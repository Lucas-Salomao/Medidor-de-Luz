#include <stdio.h>
#include "lvgl.h"
#include "Screens.h"
#include "esp_log.h"
#include "PCF85063.h"
#include "VEML7700.h"
#include "SD_MMC.h"

static const char *TAG_MAIN_SCREEN = "FLUORIMETER_SCREEN";

// Definição dos estados da tela
typedef enum {
    SCREEN_STATE_ZEROING_PROMPT,
    SCREEN_STATE_MEASURE_PROMPT,
    SCREEN_STATE_SHOW_RESULT,
} screen_state_t;

// Variáveis de estado e componentes da UI
static screen_state_t current_state;
static lv_obj_t *datetime_label = NULL;
static lv_obj_t *instruction_label = NULL;  // Rótulo para instruções
static lv_obj_t *value_label = NULL;        // Rótulo para exibir o valor de lux
static lv_obj_t *zero_btn = NULL;
static lv_obj_t *measure_btn = NULL;
static lv_obj_t *save_btn = NULL;
static lv_obj_t *repeat_btn = NULL;

static float lux_offset = 0.0f;
static float last_measurement = 0.0f;
static char datetime_str[50];

// Declarações de funções
static void update_datetime_label(void);
static void datetime_update_task(void *arg);
void config_btn_event_handler(lv_event_t *e);
static void update_ui_for_state(screen_state_t new_state);
static void zero_btn_event_handler(lv_event_t *e);
static void measure_btn_event_handler(lv_event_t *e);
static void save_btn_event_handler(lv_event_t *e);
static void repeat_btn_event_handler(lv_event_t *e);
static void zero_sensor_task(void *pvParameters);


// Função para atualizar a data e hora no rodapé
static void update_label_async(void *data) {
    lv_label_set_text(datetime_label, datetime_str);
}

void update_datetime_label(void) {
    if (datetime_label == NULL) return;
    PCF85063_Read_Time(&datetime);
    const char *weekday_str[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    snprintf(datetime_str, sizeof(datetime_str), "%s %02d/%02d/%04d %02d:%02d:%02d",
             weekday_str[datetime.dotw], datetime.day, datetime.month, datetime.year,
             datetime.hour, datetime.minute, datetime.second);
    if (lv_obj_is_valid(datetime_label)) {
        lv_async_call(update_label_async, NULL);
    }
}

// Tarefa para atualizar a data e hora periodicamente
static void datetime_update_task(void *arg) {
    while (1) {
        update_datetime_label();
        vTaskDelay(pdMS_TO_TICKS(1000));
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

// Gerencia a visibilidade dos objetos da UI com base no estado
static void update_ui_for_state(screen_state_t new_state) {
    current_state = new_state;

    // Oculta todos os botões de ação
    lv_obj_add_flag(zero_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(measure_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(save_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(repeat_btn, LV_OBJ_FLAG_HIDDEN);

    switch (current_state) {
        case SCREEN_STATE_ZEROING_PROMPT:
            lv_label_set_text(instruction_label, "Place the blank for zeroing");
            lv_label_set_text(value_label, "Lux: --");
            lv_obj_clear_flag(zero_btn, LV_OBJ_FLAG_HIDDEN);
            break;

        case SCREEN_STATE_MEASURE_PROMPT:
            lv_label_set_text(instruction_label, "Insert the sample");
            lv_label_set_text(value_label, "Lux: 0.00");
            lv_obj_clear_flag(measure_btn, LV_OBJ_FLAG_HIDDEN);
            break;

        case SCREEN_STATE_SHOW_RESULT:
            lv_label_set_text(instruction_label, "Measurement completed");
            lv_obj_clear_flag(save_btn, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(repeat_btn, LV_OBJ_FLAG_HIDDEN);
            break;
    }
}

// Tarefa para zerar o sensor
static void zero_sensor_task(void *pvParameters) {
    lv_label_set_text(value_label, "Zeroing...");
    
    // Parâmetros de zeramento
    const int num_reads = 10;
    const int delay_ms = 50;
    float lux_sum = 0.0f;
    int successful_reads = 0;

    for (int i = 0; i < num_reads; i++) {
        float lux;
        if (VEML7700_Read_Lux(&lux) == ESP_OK) {
            lux_sum += lux;
            successful_reads++;
        }
        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }

    if (successful_reads > 0) {
        lux_offset = lux_sum / successful_reads;
        ESP_LOGI(TAG_MAIN_SCREEN, "Zeroing complete. Offset: %.2f lux", lux_offset);
        update_ui_for_state(SCREEN_STATE_MEASURE_PROMPT);
    } else {
        ESP_LOGE(TAG_MAIN_SCREEN, "Failed to zero sensor.");
        lv_label_set_text(value_label, "Error zeroing!");
        vTaskDelay(pdMS_TO_TICKS(2000));
        update_ui_for_state(SCREEN_STATE_ZEROING_PROMPT);
    }

    vTaskDelete(NULL);
}

//--- Callbacks de botões ---

static void zero_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG_MAIN_SCREEN, "Zero button clicked");
    xTaskCreate(zero_sensor_task, "zero_task", 4096, NULL, 5, NULL);
}

static void measure_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG_MAIN_SCREEN, "Measure button clicked");
    float lux;
    if (VEML7700_Read_Lux(&lux) == ESP_OK) {
        last_measurement = lux - lux_offset;
        if (last_measurement < 0) last_measurement = 0.0;

        char buf[32];
        snprintf(buf, sizeof(buf), "Lux: %.2f", last_measurement);
        lv_label_set_text(value_label, buf);

        update_ui_for_state(SCREEN_STATE_SHOW_RESULT);
    } else {
        lv_label_set_text(value_label, "Read Error!");
    }
}

static void save_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG_MAIN_SCREEN, "Save button clicked");
    
    // Abre o arquivo em modo "append+" (cria se não existir)
    FILE* f = fopen("/sdcard/measurements.csv", "a+");
    if (f == NULL) {
        ESP_LOGE(TAG_MAIN_SCREEN, "Failed to open measurements.csv for appending.");
        lv_label_set_text(instruction_label, "SD Card Error!");
        lv_timer_t *t = lv_timer_create( (void*)update_ui_for_state, 2000, (void*)SCREEN_STATE_ZEROING_PROMPT);
        lv_timer_set_repeat_count(t, 1);
        return;
    }

    // Verifica se o arquivo está vazio para escrever o cabeçalho
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    if (size == 0) {
        fprintf(f, "Measurement,Time\n");
        ESP_LOGI(TAG_MAIN_SCREEN, "CSV header written to measurements.csv");
    }

    // Garante que o timestamp está atualizado e o anexa ao arquivo
    update_datetime_label(); 
    fprintf(f, "%.2f,\"%s\"\n", last_measurement, datetime_str);
    fclose(f);

    ESP_LOGI(TAG_MAIN_SCREEN, "Data saved to CSV.");
    lv_label_set_text(instruction_label, "Saved!");

    // Retorna ao estado inicial após um tempo
    lv_timer_t *timer = lv_timer_create((void*)update_ui_for_state, 1500, (void*)SCREEN_STATE_ZEROING_PROMPT);
    lv_timer_set_repeat_count(timer, 1);
}

static void repeat_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG_MAIN_SCREEN, "Repeat button clicked");
    update_ui_for_state(SCREEN_STATE_MEASURE_PROMPT);
}


// Função para criar a tela principal (fluxímetro)
void create_main_screen(lv_obj_t *parent) {
    // Título
    lv_obj_t *title = lv_label_create(parent);
    lv_label_set_text(title, "FLUORIMETER");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(title, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

    // Botão de Configurações
    lv_obj_t *config_btn = lv_btn_create(parent);
    lv_obj_set_size(config_btn, 40, 40);
    lv_obj_align(config_btn, LV_ALIGN_TOP_RIGHT, -5, 5);
    lv_obj_add_event_cb(config_btn, config_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *gear_icon = lv_label_create(config_btn);
    lv_label_set_text(gear_icon, LV_SYMBOL_SETTINGS);
    lv_obj_center(gear_icon);

    // Rótulo para instruções
    instruction_label = lv_label_create(parent);
    lv_obj_set_width(instruction_label, 220); // Para quebra de linha
    lv_obj_set_style_text_align(instruction_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(instruction_label, LV_ALIGN_CENTER, 0, -60);
    lv_label_set_long_mode(instruction_label, LV_LABEL_LONG_WRAP);

    // Rótulo para valor do sensor
    value_label = lv_label_create(parent);
    lv_obj_align(value_label, LV_ALIGN_CENTER, 0, -20);
    lv_obj_set_style_text_font(value_label, &lv_font_montserrat_16, 0);

    // --- Botões de Ação ---
    // Botão "Zero"
    zero_btn = lv_btn_create(parent);
    lv_obj_set_size(zero_btn, 120, 50);
    lv_obj_align(zero_btn, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_event_cb(zero_btn, zero_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *label_zero = lv_label_create(zero_btn);
    lv_label_set_text(label_zero, "Zero");
    lv_obj_center(label_zero);

    // Botão "Measure"
    measure_btn = lv_btn_create(parent);
    lv_obj_set_size(measure_btn, 120, 50);
    lv_obj_align(measure_btn, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_event_cb(measure_btn, measure_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *label_measure = lv_label_create(measure_btn);
    lv_label_set_text(label_measure, "Measure");
    lv_obj_center(label_measure);

    // Botão "Save"
    save_btn = lv_btn_create(parent);
    lv_obj_set_size(save_btn, 100, 50);
    lv_obj_align(save_btn, LV_ALIGN_CENTER, -60, 40);
    lv_obj_add_event_cb(save_btn, save_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *label_save = lv_label_create(save_btn);
    lv_label_set_text(label_save, "Save");
    lv_obj_center(label_save);

    // Botão "Repeat"
    repeat_btn = lv_btn_create(parent);
    lv_obj_set_size(repeat_btn, 100, 50);
    lv_obj_align(repeat_btn, LV_ALIGN_CENTER, 60, 40);
    lv_obj_add_event_cb(repeat_btn, repeat_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *label_repeat = lv_label_create(repeat_btn);
    lv_label_set_text(label_repeat, "Repeat");
    lv_obj_center(label_repeat);

    // Rótulo de data e hora no rodapé
    datetime_label = lv_label_create(parent);
    lv_obj_set_style_text_font(datetime_label, &lv_font_montserrat_12, 0);
    lv_obj_set_style_text_color(datetime_label, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(datetime_label, LV_ALIGN_BOTTOM_MID, 0, -5);

    // Inicializa o estado da UI
    update_ui_for_state(SCREEN_STATE_ZEROING_PROMPT);

    // Inicializa a data e hora imediatamente e cria a tarefa de atualização
    update_datetime_label();
    xTaskCreate(datetime_update_task, "datetime_update_task", 4096, NULL, 5, NULL);
}