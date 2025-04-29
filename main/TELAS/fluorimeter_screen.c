#include <stdio.h>
#include "lvgl.h"
#include "Screens.h" // Inclui o cabeçalho da tela de configurações
#include "esp_log.h"
#include "PCF85063.h" // Inclui o cabeçalho do RTC
#include "VEML7700.h"

static lv_obj_t *datetime_label = NULL; // Rótulo para data e hora no rodapé
static const char *TAG_MAIN_SCREEN = "TAG_MAIN_SCREEN";
static char datetime_str[50];
static uint8_t medidas = 10;
static uint8_t delay_medidas = 50;
static float lux_offset = 0.0f; // Offset de zeramento do sensor
static lv_obj_t *id_input = NULL;
static lv_obj_t *keyboard = NULL; // Objeto do teclado

static void id_input_event_handler(lv_event_t *e);
static void screen_click_event_handler(lv_event_t *e);
static void keyboard_close_handler(lv_event_t *e);  

void update_lux_value(float lux) {
    char buf[32];
    float adjusted_lux = lux - lux_offset; // Aplica o offset
    if (adjusted_lux < 0.0f) adjusted_lux = 0.0f; // Evita valores negativos
    snprintf(buf, sizeof(buf), "Lux: %.2f", adjusted_lux);
    lv_label_set_text(lux_label, buf);
}

// Função auxiliar para atualizar o rótulo no thread do LVGL
static void update_label_async(void *data) {
    lv_label_set_text(datetime_label, datetime_str);
}

// Função para atualizar a data e hora no rodapé
void update_datetime_label(void) {
    if (datetime_label == NULL) {
        ESP_LOGE(TAG_MAIN_SCREEN, "datetime_label não inicializado");
        return;
    }

    // Lê a hora atual do RTC
    PCF85063_Read_Time(&datetime);

    // Formata a string de data e hora
    const char *weekday_str[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    snprintf(datetime_str, sizeof(datetime_str), "%s %02d/%02d/%04d %02d:%02d:%02d", weekday_str[datetime.dotw],datetime.day, datetime.month, datetime.year, datetime.hour, datetime.minute, datetime.second);
    
    // Atualiza o rótulo no thread do LVGL
    lv_async_call(update_label_async, NULL);
}

// Tarefa para atualizar a data e hora periodicamente
static void datetime_update_task(void *arg) {
    while (1) {
        update_datetime_label();
        vTaskDelay(pdMS_TO_TICKS(1000)); // Atualiza a cada 1 segundo
    }
}

void config_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG_MAIN_SCREEN, "Clique no botão de configuração");
    if (config_screen == NULL) {
        ESP_LOGE(TAG_MAIN_SCREEN, "config_screen não inicializado");
        return;
    }
    ESP_LOGI(TAG_MAIN_SCREEN, "Tentando carregar a tela de configuração");
    // lv_disp_load_scr(config_screen);
    lv_scr_load_anim(config_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

// Funções estáticas para atualizações assíncronas
static void set_zerando_label(void *data) {
    lv_label_set_text(lux_label, "Zerando...");
}

static void set_zerado_label(void *data) {
    lv_label_set_text(lux_label, "Zerado! Lux: 0.00");
}

static void set_erro_zerar_label(void *data) {
    lv_label_set_text(lux_label, "Erro ao zerar");
}

// Função para realizar o zeramento do sensor
void zero_sensor_task(lv_event_t *e) {
    ESP_LOGI("SENSOR TASK", "Iniciando tarefa de zeramento");

    float lux_sum = 0.0f;
    int successful_reads = 0;
    const int num_reads = medidas;
    const int delay_ms = delay_medidas;

    // Exibe mensagem na interface indicando que o zeramento está em andamento
    lv_async_call(set_zerando_label, NULL);

    // Realiza as leituras para zeramento
    for (int i = 0; i < num_reads; i++) {
        float lux;
        if (VEML7700_Read_Lux(&lux) == ESP_OK) {
            lux_sum += lux;
            successful_reads++;
            ESP_LOGI("SENSOR TASK", "Leitura de zeramento %d: %.2f lux", i + 1, lux);
        } else {
            ESP_LOGE("SENSOR TASK", "Falha na leitura de zeramento %d", i + 1);
        }
        vTaskDelay(pdMS_TO_TICKS(delay_ms)); // Aguarda antes da próxima leitura
    }

    // Verifica se houve leituras bem-sucedidas
    if (successful_reads > 0) {
        lux_offset = lux_sum / successful_reads; // Define o offset como a média
        ESP_LOGI("SENSOR TASK", "Zeramento concluído. Offset: %.2f lux", lux_offset);
        lv_async_call(set_zerado_label, NULL);
    } else {
        ESP_LOGE("SENSOR TASK", "Nenhuma leitura bem-sucedida para zeramento");
        lv_async_call(set_erro_zerar_label, NULL);
    }
    vTaskDelete(NULL);
}

void zero_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG_MAIN_SCREEN, "Clique no botão de zeramento");
    xTaskCreatePinnedToCore(zero_sensor_task, "Zero Sensor Task", 4096, NULL, 2, NULL, 0);   
    
}

// Função para carregar a tela do fluxímetro
void create_main_screen(lv_obj_t *parent) {
    
    // Adiciona evento de clique na tela para fechar o teclado
    lv_obj_add_event_cb(parent, screen_click_event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t *title = lv_label_create(parent);
    lv_label_set_text(title, "FLUORIMETER");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(title, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

    lux_label = lv_label_create(parent);
    lv_label_set_text(lux_label, "Lux: --");
    lv_obj_set_style_text_font(lux_label, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(lux_label, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(lux_label, LV_ALIGN_TOP_MID, 0, 70);

    lv_obj_t *config_btn = lv_btn_create(parent);
    lv_obj_set_size(config_btn, 40, 40);
    lv_obj_align(config_btn, LV_ALIGN_TOP_RIGHT, -5, 5);
    lv_obj_add_event_cb(config_btn, config_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *gear_icon = lv_label_create(config_btn);
    lv_label_set_text(gear_icon, LV_SYMBOL_SETTINGS);
    lv_obj_center(gear_icon);

    // Rótulo de data e hora no rodapé
    datetime_label = lv_label_create(parent);
    // lv_label_set_text(datetime_label, "Data/Hora: --");
    lv_obj_set_style_text_font(datetime_label, &lv_font_montserrat_12, 0); // Fonte menor para o rodapé
    lv_obj_set_style_text_color(datetime_label, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(datetime_label, LV_ALIGN_BOTTOM_MID, 0, -5);

    // Inicializa a data e hora imediatamente
    update_datetime_label();

    // Cria a tarefa para atualizar a data e hora
    xTaskCreate(datetime_update_task, "datetime_update_task", 4096, NULL, 5, NULL);


    // Cria o botão "Zeroing" (ou "Zero") com ícone
    lv_obj_t *btn_zero = lv_btn_create(parent);
    lv_obj_set_size(btn_zero, 200, 50);
    lv_obj_align(btn_zero, LV_ALIGN_CENTER, 0, -30); // Acima do centro
    lv_obj_add_event_cb(btn_zero, zero_btn_event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label_zero = lv_label_create(btn_zero);
    lv_label_set_text(label_zero, "CALIBRATE");
    lv_obj_set_style_text_font(label_zero, &lv_font_montserrat_16, 0);
    lv_obj_align(label_zero, LV_ALIGN_CENTER, 0, 0);

    // Id Label
    lv_obj_t *id_label = lv_label_create(parent);
    lv_label_set_text(id_label, "Sample identification");
    lv_obj_set_style_text_color(id_label, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(id_label, LV_ALIGN_TOP_LEFT, 20, 160);
    
    // Id Input
    id_input = lv_textarea_create(parent);
    lv_textarea_set_password_mode(id_input, false);
    lv_textarea_set_one_line(id_input, true);
    lv_obj_set_size(id_input, 200, 40);
    lv_obj_align(id_input, LV_ALIGN_TOP_LEFT, 20, 180);
    lv_obj_add_event_cb(id_input, id_input_event_handler, LV_EVENT_CLICKED, NULL);

    // Inicializa o teclado
    keyboard = lv_keyboard_create(parent);
    lv_obj_set_size(keyboard, 240, 120);
    lv_obj_align(keyboard, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_keyboard_set_textarea(keyboard, id_input);
    lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
    lv_keyboard_set_mode(keyboard, LV_KEYBOARD_MODE_TEXT_LOWER);
    // Adiciona evento para fechar o teclado ao pressionar "OK"
    lv_obj_add_event_cb(keyboard, keyboard_close_handler, LV_EVENT_READY, NULL);
    
}

static void id_input_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG, "ID input clicked");
    // Mostra o teclado
    if (keyboard != NULL) {
        lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
        lv_keyboard_set_textarea(keyboard, id_input);
    }
}

static void screen_click_event_handler(lv_event_t *e) {
    // Fecha o teclado se o clique for fora do password_input
    lv_obj_t *target = lv_event_get_target(e);
    if (target != id_input && keyboard != NULL && !lv_obj_has_flag(keyboard, LV_OBJ_FLAG_HIDDEN)) {
        lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
        ESP_LOGI(TAG, "Keyboard hidden due to screen click");
    }
}

static void keyboard_close_handler(lv_event_t *e) {
    // Fecha o teclado quando o botão "OK" for pressionado
    if (keyboard != NULL) {
        lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
        ESP_LOGI(TAG, "Keyboard hidden due to OK button");
    }
}
