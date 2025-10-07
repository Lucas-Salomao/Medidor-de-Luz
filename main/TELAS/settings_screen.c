#include <stdio.h>
#include "lvgl.h"
#include "clock_settings_screen.h"
#include "wifi_settings_screen.h"
#include "font_awesome_icons.h"
#include "Screens.h"
#include "esp_log.h"
#include "internationalization.h"
#include "Fonts/custom_fonts.h"

static const char *TAG_SETTINGS_SCREEN = "TAG_SETTINGS_SCREEN";
static lv_style_t fa_icon_style;
#define ICON_CLOCK "\xEF\x80\x97"

// Make UI components static to be accessible from update functions
static lv_obj_t *title_label;
static lv_obj_t *clock_btn_label;
static lv_obj_t *wifi_btn_label;
static lv_obj_t *language_label;
static lv_obj_t *language_dropdown;

void make_styles(void) {
    lv_style_init(&fa_icon_style);
    lv_style_set_text_font(&fa_icon_style, &font_awesome_icons);
    lv_style_set_text_color(&fa_icon_style, lv_color_white());
}

void settings_screen_update_texts(void) {
    lv_label_set_text(title_label, get_string(STRING_SETTINGS));
    lv_label_set_text(clock_btn_label, get_string(STRING_CLOCK_SETTINGS));
    lv_label_set_text(wifi_btn_label, get_string(STRING_WIFI_SETTINGS));
    lv_label_set_text(language_label, get_string(STRING_LANGUAGE));

    char lang_options[100];
    snprintf(lang_options, sizeof(lang_options), "%s\n%s\n%s",
             get_string(STRING_LANG_PORTUGUESE),
             get_string(STRING_LANG_ENGLISH),
             get_string(STRING_LANG_SPANISH));
    lv_dropdown_set_options(language_dropdown, lang_options);
}

// Event handler for the language dropdown
void settings_language_dropdown_event_handler(lv_event_t *e) {
    lv_obj_t *dropdown = lv_event_get_target(e);
    uint16_t selected_index = lv_dropdown_get_selected(dropdown);

    language_t selected_lang;
    if (selected_index == 0) {
        selected_lang = LANG_PT_BR;
    } else if (selected_index == 1) {
        selected_lang = LANG_EN;
    } else {
        selected_lang = LANG_ES;
    }

    if (selected_lang != get_language()) {
        set_language(selected_lang); // This will trigger the UI update via a central function later
    }
}


// Callback para o botão Relógio
void btn_clock_cb(lv_event_t *e) {
    ESP_LOGI(TAG_SETTINGS_SCREEN, "Botão de configuração do relógio clicado");
    clock_settings_screen_load(); // Carrega a tela de configurações do relógio
}

// Callback para o botão Wi-Fi
void btn_wifi_cb(lv_event_t *e) {
    wifi_settings_screen_load(); // Carrega a tela de configurações do Wi-Fi
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
    make_styles();
    lv_obj_set_style_bg_color(parent, lv_color_white(), LV_PART_MAIN);

    title_label = lv_label_create(parent); // Use static variable
    lv_label_set_text(title_label, get_string(STRING_SETTINGS)); // Internationalized
    lv_obj_set_style_text_font(title_label, &montserrat_pt_16, 0);
    lv_obj_set_style_text_color(title_label, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *home_btn = lv_btn_create(parent);
    lv_obj_set_size(home_btn, 40, 40);
    lv_obj_align(home_btn, LV_ALIGN_TOP_LEFT, 5, 5);
    lv_obj_add_event_cb(home_btn, home_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *gear_icon = lv_label_create(home_btn);
    lv_label_set_text(gear_icon, LV_SYMBOL_HOME);
    lv_obj_center(gear_icon);

    // Cria o botão "Relógio"
    lv_obj_t *btn_clock = lv_btn_create(parent);
    lv_obj_set_size(btn_clock, 180, 50);
    lv_obj_align(btn_clock, LV_ALIGN_CENTER, 0, -60);

    clock_btn_label = lv_label_create(btn_clock); // Use static variable
    lv_label_set_text(clock_btn_label, get_string(STRING_CLOCK_SETTINGS)); // Internationalized
    lv_obj_align(clock_btn_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *clock_icon = lv_label_create(btn_clock);
    lv_label_set_text(clock_icon, ICON_CLOCK);
    lv_obj_add_style(clock_icon, &fa_icon_style, 0);
    lv_obj_align(clock_icon, LV_ALIGN_LEFT_MID, 5, 0);

    // Cria o botão "Wi-Fi"
    lv_obj_t *btn_wifi = lv_btn_create(parent);
    lv_obj_set_size(btn_wifi, 180, 50);
    lv_obj_align(btn_wifi, LV_ALIGN_CENTER, 0, 0);

    wifi_btn_label = lv_label_create(btn_wifi); // Use static variable
    lv_label_set_text(wifi_btn_label, get_string(STRING_WIFI_SETTINGS)); // Internationalized
    lv_obj_center(wifi_btn_label);

    lv_obj_t *wifi_icon = lv_label_create(btn_wifi);
    lv_label_set_text(wifi_icon, LV_SYMBOL_WIFI);
    lv_obj_align(wifi_icon, LV_ALIGN_LEFT_MID, 5, 0);

    // Language Label
    language_label = lv_label_create(parent); // Use static variable
    lv_label_set_text(language_label, get_string(STRING_LANGUAGE)); // Internationalized
    lv_obj_set_style_text_font(language_label, &montserrat_pt_12, 0);
    lv_obj_set_style_text_color(language_label, lv_color_black(), 0);
    lv_obj_align(language_label, LV_ALIGN_CENTER, -40, 60);

    // Language Dropdown
    language_dropdown = lv_dropdown_create(parent);
    char lang_options[100];
    snprintf(lang_options, sizeof(lang_options), "%s\n%s\n%s",
             get_string(STRING_LANG_PORTUGUESE),
             get_string(STRING_LANG_ENGLISH),
             get_string(STRING_LANG_SPANISH));
    lv_dropdown_set_options(language_dropdown, lang_options);
    lv_obj_set_style_text_font(language_dropdown, &montserrat_pt_12, LV_PART_MAIN);
    lv_obj_set_style_text_font(language_dropdown, &montserrat_pt_12, LV_PART_ITEMS);
    lv_obj_align(language_dropdown, LV_ALIGN_CENTER, 60, 60);
    lv_obj_add_event_cb(language_dropdown, settings_language_dropdown_event_handler, LV_EVENT_VALUE_CHANGED, NULL);

    // Set selected language
    language_t current_lang = get_language();
    if (current_lang == LANG_PT_BR) {
        lv_dropdown_set_selected(language_dropdown, 0);
    } else if (current_lang == LANG_EN) {
        lv_dropdown_set_selected(language_dropdown, 1);
    } else if (current_lang == LANG_ES) {
        lv_dropdown_set_selected(language_dropdown, 2);
    }

    lv_obj_add_event_cb(btn_clock, btn_clock_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_wifi, btn_wifi_cb, LV_EVENT_CLICKED, NULL);
}
