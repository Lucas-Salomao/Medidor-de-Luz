#include <stdio.h>
#include "lvgl.h"
#include "Screens.h" // Inclui o cabeçalho da tela de configurações
#include "esp_log.h"
#include "PCF85063.h" // Inclui o cabeçalho do RTC

static lv_obj_t *datetime_label = NULL; // Rótulo para data e hora no rodapé
static const char *TAG_MAIN_SCREEN = "TAG_MAIN_SCREEN";
static char datetime_str[50];

void update_lux_value(float lux) {
    char buf[32];
    snprintf(buf, sizeof(buf), "Lux: %.2f", lux);
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

// Função para carregar a tela do fluxímetro
void create_main_screen(lv_obj_t *parent) {
    lv_obj_t *title = lv_label_create(parent);
    lv_label_set_text(title, "FLUORIMETER");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(title, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

    lux_label = lv_label_create(parent);
    lv_label_set_text(lux_label, "Lux: --");
    lv_obj_set_style_text_font(lux_label, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(lux_label, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(lux_label, LV_ALIGN_CENTER, 0, 30);

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

    lv_obj_t *label_clock = lv_label_create(btn_zero);
    lv_label_set_text(label_clock, "ZEROING");
    lv_obj_set_style_text_font(label_clock, &lv_font_montserrat_16, 0);
    lv_obj_align(label_clock, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *clock_icon = lv_label_create(btn_clock);
    lv_label_set_text(clock_icon, ICON_CLOCK);
    lv_obj_add_style(clock_icon, &fa_icon_style, 0);  // Aplica o estilo da fonte
    lv_obj_align(clock_icon, LV_ALIGN_LEFT_MID, 5, 0);  // Posiciona o ícone à esquerda
}

//f4f3
