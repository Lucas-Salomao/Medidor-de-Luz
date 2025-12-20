#include <stdio.h>
#include "lvgl.h"
#include "clock_settings_screen.h"
#include "wifi_settings_screen.h"
#include "Screens.h" // Inclui o cabeçalho da tela de configurações
#include "esp_log.h"
#include "../Languages/internationalization.h"
#include "../OTA_Manager/OTA_Manager.h"

static const char *TAG_SETTINGS_SCREEN = "TAG_SETTINGS_SCREEN";

void create_config_screen(lv_obj_t *parent);

// Event handler for the language dropdown
static void language_dropdown_event_handler(lv_event_t *e) {
    lv_obj_t *dropdown = lv_event_get_target(e);
    uint16_t selected_index = lv_dropdown_get_selected(dropdown);

    language_t new_lang = (language_t)selected_index;

    if (new_lang != get_language()) {
        set_language(new_lang);
        lv_timer_t *timer = lv_timer_create(reinit_ui_task, 10, NULL); // Schedule UI re-initialization
        lv_timer_set_repeat_count(timer, 1);
    }
}

// Callback para o botão Relógio
void btn_clock_cb(lv_event_t *e) {
    ESP_LOGI(TAG_SETTINGS_SCREEN, "Botão de configuração do relógio clicado");
    clock_settings_screen_load();
}

// Callback para o botão Wi-Fi
void btn_wifi_cb(lv_event_t *e) {
    wifi_settings_screen_load();
}

// Callback for the OTA update button
void btn_ota_update_cb(lv_event_t *e) {
    ESP_LOGI(TAG_SETTINGS_SCREEN, "Check for update button clicked");
    // IMPORTANT: Make sure Wi-Fi is connected before starting the update.
    ota_manager_check_for_update();
}

void home_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG_SETTINGS_SCREEN, "Clique no botão de home");
    if (main_screen == NULL) {
        ESP_LOGE(TAG_SETTINGS_SCREEN, "main_screen não inicializado");
        return;
    }
    ESP_LOGI(TAG_SETTINGS_SCREEN, "Tentando carregar a tela principal");
    lv_scr_load_anim(main_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

// Função para carregar a tela de configurações
void create_config_screen(lv_obj_t *parent) {
    lv_obj_set_style_bg_color(parent, lv_color_white(), LV_PART_MAIN);

    lv_obj_t *title = lv_label_create(parent);
    lv_label_set_text(title, get_string(STRING_SETTINGS));
    lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(title, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 5);

    lv_obj_t *home_btn = lv_btn_create(parent);
    lv_obj_set_size(home_btn, 40, 40);
    lv_obj_align(home_btn, LV_ALIGN_TOP_LEFT, 5, 5);
    lv_obj_add_event_cb(home_btn, home_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *gear_icon = lv_label_create(home_btn);
    lv_label_set_text(gear_icon, LV_SYMBOL_HOME);
    lv_obj_center(gear_icon);

    // Cria o botão "Relógio"
    lv_obj_t *btn_clock = lv_btn_create(parent);
    lv_obj_set_size(btn_clock, 180, 45);
    lv_obj_align(btn_clock, LV_ALIGN_TOP_MID, 0, 35);
    lv_obj_add_event_cb(btn_clock, btn_clock_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label_clock = lv_label_create(btn_clock);
    lv_label_set_text(label_clock, get_string(STRING_CLOCK_SETTINGS));
    lv_obj_center(label_clock);

    // Cria o botão "Wi-Fi"
    lv_obj_t *btn_wifi = lv_btn_create(parent);
    lv_obj_set_size(btn_wifi, 180, 45);
    lv_obj_align(btn_wifi, LV_ALIGN_TOP_MID, 0, 85);
    lv_obj_add_event_cb(btn_wifi, btn_wifi_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label_wifi = lv_label_create(btn_wifi);
    lv_label_set_text(label_wifi, get_string(STRING_WIFI_SETTINGS));
    lv_obj_center(label_wifi);

    // Cria o botão "Verificar Atualizações"
    lv_obj_t *btn_ota = lv_btn_create(parent);
    lv_obj_set_size(btn_ota, 180, 45);
    lv_obj_align(btn_ota, LV_ALIGN_TOP_MID, 0, 135);
    lv_obj_add_event_cb(btn_ota, btn_ota_update_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label_ota = lv_label_create(btn_ota);
    lv_label_set_text(label_ota, get_string(STRING_CHECK_UPDATES));
    lv_obj_center(label_ota);

    // Container para o seletor de idiomas
    lv_obj_t *lang_container = lv_obj_create(parent);
    lv_obj_remove_style_all(lang_container);
    lv_obj_set_size(lang_container, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align(lang_container, LV_ALIGN_BOTTOM_MID, 0, -5);
    lv_obj_set_flex_flow(lang_container, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(lang_container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_column(lang_container, 10, 0);

    lv_obj_t *lang_label = lv_label_create(lang_container);
    lv_label_set_text(lang_label, get_string(STRING_LANGUAGE));
    lv_obj_set_style_text_color(lang_label, lv_color_black(), LV_PART_MAIN);

    lv_obj_t *lang_dropdown = lv_dropdown_create(lang_container);
    char lang_options[100];
    snprintf(lang_options, sizeof(lang_options), "%s\n%s\n%s",
             get_string(STRING_LANG_ENGLISH),
             get_string(STRING_LANG_SPANISH),
             get_string(STRING_LANG_PORTUGUESE));
    lv_dropdown_set_options(lang_dropdown, lang_options);
    lv_obj_add_event_cb(lang_dropdown, language_dropdown_event_handler, LV_EVENT_VALUE_CHANGED, NULL);
    lv_dropdown_set_selected(lang_dropdown, get_language());
}
