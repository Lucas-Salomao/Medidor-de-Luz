#include "lvgl.h"
#include "clock_settings_screen.h"
#include "wifi_settings_screen.h"
#include "font_awesome_icons.h"
#include "Screens.h" // Inclui o cabeçalho da tela de configurações
#include "esp_log.h"


static const char *TAG_SETTINGS_SCREEN = "TAG_SETTINGS_SCREEN";
static lv_style_t fa_icon_style;
#define ICON_CLOCK "\xEF\x80\x97"

void make_styles(void) {
    lv_style_init(&fa_icon_style);
    lv_style_set_text_font(&fa_icon_style, &font_awesome_icons);
    lv_style_set_text_color(&fa_icon_style, lv_color_white());  // Alterado para preto para combinar com o fundo branco
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
    // lv_disp_load_scr(main_screen);
    lv_scr_load_anim(main_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

// Função para carregar a tela de configurações
void create_config_screen(lv_obj_t *parent) {
    make_styles();
    lv_obj_set_style_bg_color(parent, lv_color_white(), LV_PART_MAIN);

    lv_obj_t *title = lv_label_create(parent);
    lv_label_set_text(title, "SETTINGS");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(title, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

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
    lv_obj_align(btn_clock, LV_ALIGN_CENTER, 0, -30); // Acima do centro

    lv_obj_t *label_clock = lv_label_create(btn_clock);
    lv_label_set_text(label_clock, "Clock Settings");
    lv_obj_align(label_clock, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *clock_icon = lv_label_create(btn_clock);
    lv_label_set_text(clock_icon, ICON_CLOCK);
    lv_obj_add_style(clock_icon, &fa_icon_style, 0);  // Aplica o estilo da fonte
    lv_obj_align(clock_icon, LV_ALIGN_LEFT_MID, 5, 0);  // Posiciona o ícone à esquerda

    // Cria o botão "Wi-Fi"
    lv_obj_t *btn_wifi = lv_btn_create(parent);
    lv_obj_set_size(btn_wifi, 180, 50);
    lv_obj_align(btn_wifi, LV_ALIGN_CENTER, 0, 30); // Abaixo do centro

    lv_obj_t *label_wifi = lv_label_create(btn_wifi);
    lv_label_set_text(label_wifi, "Wi-Fi");
    lv_obj_center(label_wifi);

    lv_obj_t *wifi_icon = lv_label_create(btn_wifi);
    lv_label_set_text(wifi_icon, LV_SYMBOL_WIFI);
    lv_obj_align(wifi_icon, LV_ALIGN_LEFT_MID, 5, 0);  // Posiciona o ícone à esquerda

    // // Estiliza os botões
    // static lv_style_t style_btn;
    // lv_style_init(&style_btn);
    // lv_style_set_bg_color(&style_btn, lv_color_make(0xE0, 0xE0, 0xE0)); // Cinza claro
    // lv_style_set_border_width(&style_btn, 1);
    // lv_style_set_border_color(&style_btn, lv_color_black());
    // lv_style_set_text_font(&style_btn, &lv_font_montserrat_16);
    // lv_obj_add_style(btn_clock, &style_btn, 0);
    // lv_obj_add_style(btn_wifi, &style_btn, 0);

    lv_obj_add_event_cb(btn_clock, btn_clock_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_add_event_cb(btn_wifi, btn_wifi_cb, LV_EVENT_CLICKED, NULL);
}