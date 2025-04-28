#include <stdio.h>
#include "lvgl.h"
#include "Screens.h" // Inclui o cabeçalho da tela de configurações
#include "esp_log.h"

void update_lux_value(float lux) {
    char buf[32];
    snprintf(buf, sizeof(buf), "Lux: %.2f", lux);
    lv_label_set_text(lux_label, buf);
}

void config_btn_event_handler(lv_event_t *e) {
    // ESP_LOGI(TAG, "Clique no botão de configuração");
    if (config_screen == NULL) {
        ESP_LOGE(TAG, "config_screen não inicializado");
        return;
    }
    // ESP_LOGI(TAG, "Tentando carregar a tela de configuração");
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
    lv_obj_align(lux_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *config_btn = lv_btn_create(parent);
    lv_obj_set_size(config_btn, 40, 40);
    lv_obj_align(config_btn, LV_ALIGN_TOP_RIGHT, -5, 5);
    lv_obj_add_event_cb(config_btn, config_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *gear_icon = lv_label_create(config_btn);
    lv_label_set_text(gear_icon, LV_SYMBOL_SETTINGS);
    lv_obj_center(gear_icon);
}

