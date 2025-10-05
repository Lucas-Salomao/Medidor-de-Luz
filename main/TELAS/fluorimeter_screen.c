#include <stdio.h>
#include <sys/stat.h>
#include "lvgl.h"
#include "Screens.h"
#include "fluorimeter_screen.h"
#include "internationalization.h"
#include "Fonts/custom_fonts.h"
#include "esp_log.h"
#include "PCF85063.h"
#include "VEML7700.h"
#include "SD_MMC.h"
#include "driver/gpio.h"
#include "PCM5101.h"

static const char *TAG_MAIN_SCREEN = "FLUORIMETER_SCREEN";

// --- Parâmetros de Medição Configuráveis ---
#define LED_PIN GPIO_NUM_15
#define MAIN_REPETITIONS 3      // Quantas vezes o ciclo de 1s de medição se repete
#define SAMPLING_DURATION_MS 1000 // Duração de cada ciclo de medição (1 segundo)
#define SAMPLING_INTERVAL_MS 100  // Intervalo entre as leituras dentro de um ciclo

// --- Nomes dos Arquivos de Áudio ---
#define AUDIO_ZERO_PROMPT    "zero_prompt.mp3"
#define AUDIO_MEASURE_PROMPT "measure_prompt.mp3"
#define AUDIO_RESULT_PROMPT  "result_prompt.mp3"

// Definição dos estados da tela
typedef enum {
    STATE_ZEROING_PROMPT,
    STATE_MEASURE_PROMPT,
    STATE_SHOW_RESULT,
} screen_state_t;

// Variáveis de estado e componentes da UI
static screen_state_t current_state;
static lv_obj_t *title_label = NULL;
static lv_obj_t *datetime_label = NULL;
static lv_obj_t *instruction_label = NULL;
static lv_obj_t *value_label = NULL;
static lv_obj_t *zero_btn = NULL;
static lv_obj_t *measure_btn = NULL;
static lv_obj_t *save_btn = NULL;
static lv_obj_t *repeat_btn = NULL;
static lv_obj_t *label_zero = NULL;
static lv_obj_t *label_measure = NULL;
static lv_obj_t *label_save = NULL;
static lv_obj_t *label_repeat = NULL;

// --- Componentes do Modal de ID ---
static lv_obj_t *id_modal_bg = NULL;    // Fundo semitransparente do modal
static lv_obj_t *id_modal_cont = NULL;  // Contêiner do modal
static lv_obj_t *id_input_textarea = NULL;
static lv_obj_t *keyboard = NULL;

static float lux_offset = 0.0f;
static float last_measurement = 0.0f;
static char datetime_str[50];

bool is_first_load = true;

// --- Declarações de Funções ---
static void update_datetime_label(void);
static void datetime_update_task(void *arg);
void config_btn_event_handler(lv_event_t *e);
static void update_ui_for_state(screen_state_t new_state);
static void zero_btn_event_handler(lv_event_t *e);
static void measure_btn_event_handler(lv_event_t *e);
static void save_btn_event_handler(lv_event_t *e);
static void repeat_btn_event_handler(lv_event_t *e);
static void zero_sensor_task(void *pvParameters);
static void measure_sensor_task(void *pvParameters);
static esp_err_t perform_measurement_sampling(float *final_avg_lux, const char* base_message);
static void return_to_zeroing_state_cb(lv_timer_t *timer);

// --- Novas declarações para o modal de ID ---
static void create_id_modal(lv_obj_t *parent);
static void id_kb_confirm_event_handler(lv_event_t *e);
static void id_modal_close_event_handler(lv_event_t *e);


// Estrutura para passar dados para a chamada assíncrona do LVGL
typedef struct {
    lv_obj_t *label;
    char text[40];
} async_label_data_t;

// --- Funções Auxiliares de UI ---
static void async_update_label_cb(void *data) {
    async_label_data_t *label_data = (async_label_data_t *)data;
    if (label_data && lv_obj_is_valid(label_data->label)) {
        lv_label_set_text(label_data->label, label_data->text);
    }
    free(label_data);
}

static void async_set_ui_state(void *data) {
    update_ui_for_state((screen_state_t)(intptr_t)data);
}

// Tarefa para atualizar a data e hora periodicamente
static void datetime_update_task(void *arg) {
    while (1) {
        update_datetime_label();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void update_datetime_label(void) {
    if (datetime_label == NULL) return;
    PCF85063_Read_Time(&datetime);
    const char *weekday_str[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    snprintf(datetime_str, sizeof(datetime_str), "%s %02d/%02d/%04d %02d:%02d:%02d",
             weekday_str[datetime.dotw], datetime.day, datetime.month, datetime.year,
             datetime.hour, datetime.minute, datetime.second);
    if (lv_obj_is_valid(datetime_label)) {
        lv_label_set_text(datetime_label, datetime_str);
    }
}

// Callback para o botão de configurações
void config_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG_MAIN_SCREEN, "Clique no botão de configuração");
    if (config_screen == NULL) {
        ESP_LOGE(TAG_MAIN_SCREEN, "config_screen não inicializado");
        return;
    }
    lv_scr_load_anim(config_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

void fluorimeter_screen_update_texts(void) {
    lv_label_set_text(title_label, get_string(STRING_FLUORIMETER));
    lv_label_set_text(label_zero, get_string(STRING_ZERO));
    lv_label_set_text(label_measure, get_string(STRING_MEASURE));
    lv_label_set_text(label_save, get_string(STRING_SAVE));
    lv_label_set_text(label_repeat, get_string(STRING_REPEAT));

    // Re-apply state-dependent text
    update_ui_for_state(current_state);
}

// Gerencia a visibilidade dos objetos da UI com base no estado
static void update_ui_for_state(screen_state_t new_state) {
    current_state = new_state;

    // Oculta todos os botões de ação
    lv_obj_add_flag(zero_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(measure_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(save_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(repeat_btn, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_text_color(instruction_label, lv_color_black(), 0);

    bool play_audio = !is_first_load;

    // Get language path for audio
    const char* lang_code = get_language_code();
    char lang_dir[20];
    snprintf(lang_dir, sizeof(lang_dir), "/sdcard/%s", lang_code);

    switch (current_state) {
        case STATE_ZEROING_PROMPT:
            lv_label_set_text(instruction_label, get_string(STRING_ZEROING_PROMPT));
            lv_label_set_text_fmt(value_label, "%s--", get_string(STRING_LUX_PREFIX));
            lv_obj_clear_flag(zero_btn, LV_OBJ_FLAG_HIDDEN);
            if (play_audio) {
                Play_Music(lang_dir, AUDIO_ZERO_PROMPT);
            }
            break;

        case STATE_MEASURE_PROMPT:
            lv_label_set_text(instruction_label, get_string(STRING_MEASURE_PROMPT));
            lv_label_set_text_fmt(value_label, "%s0.00", get_string(STRING_LUX_PREFIX));
            lv_obj_clear_flag(measure_btn, LV_OBJ_FLAG_HIDDEN);
            Play_Music(lang_dir, AUDIO_MEASURE_PROMPT);
            break;

        case STATE_SHOW_RESULT:
            lv_label_set_text(instruction_label, get_string(STRING_SHOW_RESULT));
            lv_obj_clear_flag(save_btn, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(repeat_btn, LV_OBJ_FLAG_HIDDEN);
            Play_Music(lang_dir, AUDIO_RESULT_PROMPT);
            break;
    }
}

// **NOVA FUNÇÃO para criar o modal de ID e o teclado**
static void create_id_modal(lv_obj_t *parent) {
    // Fundo semitransparente para focar no modal
    id_modal_bg = lv_obj_create(parent);
    lv_obj_remove_style_all(id_modal_bg);
    lv_obj_set_size(id_modal_bg, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(id_modal_bg, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(id_modal_bg, LV_OPA_50, 0);
    lv_obj_add_event_cb(id_modal_bg, id_modal_close_event_handler, LV_EVENT_CLICKED, NULL);

    // Contêiner principal do modal
    id_modal_cont = lv_obj_create(id_modal_bg);
    lv_obj_set_size(id_modal_cont, 220, 200);   // Tamanho do contêiner
    lv_obj_center(id_modal_cont);
    lv_obj_set_style_bg_color(id_modal_cont, lv_color_white(), 0);
    lv_obj_set_style_border_width(id_modal_cont, 0, 0);

    // Rótulo de instrução
    lv_obj_t *label = lv_label_create(id_modal_cont);
    lv_label_set_text(label, get_string(STRING_ENTER_SAMPLE_ID));
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 10, 10);

    // Área de texto para o ID
    id_input_textarea = lv_textarea_create(id_modal_cont);
    lv_obj_set_size(id_input_textarea, 200, 40);
    lv_obj_align(id_input_textarea, LV_ALIGN_TOP_LEFT, 10, 35);
    lv_textarea_set_one_line(id_input_textarea, true);
    lv_textarea_set_placeholder_text(id_input_textarea, get_string(STRING_ID));

    // Teclado
    keyboard = lv_keyboard_create(id_modal_bg); // Anexado ao fundo para posicionamento global
    lv_obj_set_size(keyboard, 240, 140);
    lv_obj_align(keyboard, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_keyboard_set_textarea(keyboard, id_input_textarea);
    lv_obj_add_event_cb(keyboard, id_kb_confirm_event_handler, LV_EVENT_READY, keyboard); // Ok/Enter
    lv_obj_add_event_cb(keyboard, id_modal_close_event_handler, LV_EVENT_CANCEL, keyboard); // Cancelar
}

// **NOVA FUNÇÃO: Callback para o 'confirmar' do teclado**
static void id_kb_confirm_event_handler(lv_event_t *e) {
    const char *sample_id = lv_textarea_get_text(id_input_textarea);
    
    if (sample_id == NULL || strlen(sample_id) == 0) {
        lv_label_set_text(instruction_label, get_string(STRING_ID_CANNOT_BE_EMPTY));
        lv_obj_set_style_text_color(instruction_label, lv_color_hex(0xFF0000), 0);
        // O modal não fecha, o usuário deve corrigir
        return;
    }

    ESP_LOGI(TAG_MAIN_SCREEN, "Saving with ID: %s", sample_id);
    
    FILE* f = fopen("/sdcard/measurements.csv", "a+");
    if (f == NULL) {
        ESP_LOGE(TAG_MAIN_SCREEN, "Failed to open measurements.csv for appending.");
        lv_label_set_text(instruction_label, get_string(STRING_SD_CARD_ERROR));
        lv_obj_set_style_text_color(instruction_label, lv_color_hex(0xFF0000), 0);
    } else {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        if (size == 0) {
            fprintf(f, "%s\n", get_string(STRING_CSV_HEADER));
            ESP_LOGI(TAG_MAIN_SCREEN, "CSV header written.");
        }

        update_datetime_label();
        fprintf(f, "\"%s\",%.2f,\"%s\"\n", sample_id, last_measurement, datetime_str);
        fclose(f);
        ESP_LOGI(TAG_MAIN_SCREEN, "Data saved to CSV.");
        lv_label_set_text(instruction_label, get_string(STRING_SAVED));
        lv_obj_set_style_text_color(instruction_label, lv_color_hex(0x008000), 0);
        const char* lang_code = get_language_code();
        char lang_dir[20];
        snprintf(lang_dir, sizeof(lang_dir), "/sdcard/%s", lang_code);
        Play_Music(lang_dir, "save_success.mp3");
    }

    // Fecha o modal e agenda o retorno ao estado inicial
    lv_obj_del(id_modal_bg);
    id_modal_bg = NULL;
    lv_timer_t *timer = lv_timer_create(return_to_zeroing_state_cb, 2000, NULL);
    lv_timer_set_repeat_count(timer, 1);
}

// **NOVA FUNÇÃO: Callback para fechar o modal (fundo ou botão de cancelar)**
static void id_modal_close_event_handler(lv_event_t *e) {
    if (id_modal_bg != NULL) {
        lv_obj_del(id_modal_bg);
        id_modal_bg = NULL; // Importante para evitar uso após deleção
        keyboard = NULL;
        id_input_textarea = NULL;
    }
}

// --- Funções de Lógica do Sensor ---

static esp_err_t perform_measurement_sampling(float *final_avg_lux, const char* base_message) {
    const int num_reads_per_cycle = SAMPLING_DURATION_MS / SAMPLING_INTERVAL_MS;
    float total_avg_sum = 0.0f;
    int successful_repetitions = 0;

    gpio_set_level(LED_PIN, 1); // Acende o LED

    for (int i = 0; i < MAIN_REPETITIONS; i++) {
        // Atualiza a UI para mostrar o progresso
        async_label_data_t *progress_data = malloc(sizeof(async_label_data_t));
        if (progress_data) {
            progress_data->label = value_label;
            snprintf(progress_data->text, sizeof(progress_data->text), "%s... (%d/%d)", base_message, i + 1, MAIN_REPETITIONS);
            lv_async_call(async_update_label_cb, progress_data);
        }

        float lux_sum_single_cycle = 0.0f;
        int successful_reads_single_cycle = 0;

        for (int j = 0; j < num_reads_per_cycle; j++) {
            float lux;
            if (VEML7700_Read_Lux(&lux) == ESP_OK) {
                lux_sum_single_cycle += lux;
                successful_reads_single_cycle++;
            }
            vTaskDelay(pdMS_TO_TICKS(SAMPLING_INTERVAL_MS));
        }
        
        if (successful_reads_single_cycle > 0) {
            total_avg_sum += (lux_sum_single_cycle / successful_reads_single_cycle);
            successful_repetitions++;
        }
    }

    gpio_set_level(LED_PIN, 0); // Apaga o LED

    if (successful_repetitions > 0) {
        *final_avg_lux = total_avg_sum / successful_repetitions;
        return ESP_OK;
    }

    return ESP_FAIL;
}

// Tarefa para zerar o sensor
static void zero_sensor_task(void *pvParameters) {
    float avg_lux;
    if (perform_measurement_sampling(&avg_lux, get_string(STRING_ZEROING)) == ESP_OK) {
        lux_offset = avg_lux;
        ESP_LOGI(TAG_MAIN_SCREEN, "Zeroing complete. Offset: %.2f lux", lux_offset);
        lv_async_call(async_set_ui_state, (void*)STATE_MEASURE_PROMPT);
    } else {
        ESP_LOGE(TAG_MAIN_SCREEN, "Failed to zero sensor.");
        async_label_data_t *err_data = malloc(sizeof(async_label_data_t));
        if(err_data){
            err_data->label = value_label;
            strcpy(err_data->text, get_string(STRING_ERROR_ZEROING));
            lv_async_call(async_update_label_cb, err_data);
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
        lv_async_call(async_set_ui_state, (void*)STATE_ZEROING_PROMPT);
    }
    vTaskDelete(NULL);
}

static void measure_sensor_task(void *pvParameters) {
    float avg_lux;
    if (perform_measurement_sampling(&avg_lux, get_string(STRING_MEASURING)) == ESP_OK) {
        last_measurement = avg_lux - lux_offset;
        if (last_measurement< 0) last_measurement = 0.0;

        async_label_data_t* res_data = malloc(sizeof(async_label_data_t));
        if(res_data){
            res_data->label = value_label;
            snprintf(res_data->text, sizeof(res_data->text), "%s%.2f", get_string(STRING_LUX_PREFIX), last_measurement);
            lv_async_call(async_update_label_cb, res_data);
        }
        
        lv_async_call(async_set_ui_state, (void*)STATE_SHOW_RESULT);
    } else {
        async_label_data_t* err_data = malloc(sizeof(async_label_data_t));
        if(err_data){
            err_data->label = value_label;
            strcpy(err_data->text, get_string(STRING_READ_ERROR));
            lv_async_call(async_update_label_cb, err_data);
        }
    }
    vTaskDelete(NULL);
}

//--- Callbacks de botões ---

static void return_to_zeroing_state_cb(lv_timer_t *timer) {
    update_ui_for_state(STATE_MEASURE_PROMPT);
}

static void zero_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG_MAIN_SCREEN, "Zero button clicked");
    xTaskCreate(zero_sensor_task, "zero_task", 4096, NULL, 5, NULL);
}

static void measure_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG_MAIN_SCREEN, "Measure button clicked");
    xTaskCreate(measure_sensor_task, "measure_task", 4096, NULL, 5, NULL);
}

// **FUNÇÃO DE SALVAR MODIFICADA: Agora abre o modal**
static void save_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG_MAIN_SCREEN, "Save button clicked, showing ID modal.");
    create_id_modal(lv_layer_top()); // Cria o modal na camada superior para sobrepor tudo
}

static void repeat_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG_MAIN_SCREEN, "Repeat button clicked");
    update_ui_for_state(STATE_MEASURE_PROMPT);
}


// Função para criar a tela principal (fluxímetro)
void create_main_screen(lv_obj_t *parent) {
    // Configura o GPIO para o LED
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_PIN),
        .mode = GPIO_MODE_OUTPUT,
    };
    gpio_config(&io_conf);
    gpio_set_level(LED_PIN, 0);

    // Título
    title_label = lv_label_create(parent);
    lv_label_set_text(title_label, get_string(STRING_FLUORIMETER));
    lv_obj_set_style_text_font(title_label, &montserrat_pt_16, 0);
    lv_obj_set_style_text_color(title_label, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 10);

    // Botão de Configurações
    lv_obj_t *config_btn = lv_btn_create(parent);
    lv_obj_set_size(config_btn, 40, 40);
    lv_obj_align(config_btn, LV_ALIGN_TOP_RIGHT, -5, 5);
    lv_obj_add_event_cb(config_btn, config_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *gear_icon = lv_label_create(config_btn);
    lv_label_set_text(gear_icon, LV_SYMBOL_SETTINGS);
    lv_obj_center(gear_icon);

    // Rótulo de instruções
    instruction_label = lv_label_create(parent);
    lv_obj_set_width(instruction_label, 220);
    lv_obj_set_style_text_align(instruction_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(instruction_label, LV_ALIGN_CENTER, 0, -60);
    lv_label_set_long_mode(instruction_label, LV_LABEL_LONG_WRAP);

    // Rótulo para valor do sensor
    value_label = lv_label_create(parent);
    lv_obj_align(value_label, LV_ALIGN_CENTER, 0, -20);
    lv_obj_set_style_text_font(value_label, &montserrat_pt_16, 0);

    // Botões de Ação
    zero_btn = lv_btn_create(parent);
    lv_obj_set_size(zero_btn, 120, 50);
    lv_obj_align(zero_btn, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_event_cb(zero_btn, zero_btn_event_handler, LV_EVENT_CLICKED, NULL);
    label_zero = lv_label_create(zero_btn);
    lv_label_set_text(label_zero, get_string(STRING_ZERO));
    lv_obj_center(label_zero);

    measure_btn = lv_btn_create(parent);
    lv_obj_set_size(measure_btn, 120, 50);
    lv_obj_align(measure_btn, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_event_cb(measure_btn, measure_btn_event_handler, LV_EVENT_CLICKED, NULL);
    label_measure = lv_label_create(measure_btn);
    lv_label_set_text(label_measure, get_string(STRING_MEASURE));
    lv_obj_center(label_measure);

    save_btn = lv_btn_create(parent);
    lv_obj_set_size(save_btn, 100, 50);
    lv_obj_align(save_btn, LV_ALIGN_CENTER, -60, 40);
    lv_obj_add_event_cb(save_btn, save_btn_event_handler, LV_EVENT_CLICKED, NULL);
    label_save = lv_label_create(save_btn);
    lv_label_set_text(label_save, get_string(STRING_SAVE));
    lv_obj_center(label_save);

    repeat_btn = lv_btn_create(parent);
    lv_obj_set_size(repeat_btn, 100, 50);
    lv_obj_align(repeat_btn, LV_ALIGN_CENTER, 60, 40);
    lv_obj_add_event_cb(repeat_btn, repeat_btn_event_handler, LV_EVENT_CLICKED, NULL);
    label_repeat = lv_label_create(repeat_btn);
    lv_label_set_text(label_repeat, get_string(STRING_REPEAT));
    lv_obj_center(label_repeat);

    // Rótulo de data e hora
    datetime_label = lv_label_create(parent);
    lv_obj_set_style_text_font(datetime_label, &montserrat_pt_12, 0);
    lv_obj_set_style_text_color(datetime_label, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(datetime_label, LV_ALIGN_BOTTOM_MID, 0, -5);

    // Inicializa o estado e a tarefa
    update_ui_for_state(STATE_ZEROING_PROMPT);
    xTaskCreate(datetime_update_task, "datetime_update_task", 4096, NULL, 5, NULL);
}