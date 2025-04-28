#include "lvgl.h"
#include "Screens.h"
#include "clock_settings_screen.h"
#include "PCF85063.h"
#include "esp_log.h"


// Componentes da UI
static lv_obj_t *hour_roller;
static lv_obj_t *minute_roller;
static lv_obj_t *day_roller;
static lv_obj_t *month_roller;
static lv_obj_t *year_roller;
static lv_obj_t *save_btn;
static lv_obj_t *back_btn;

static void back_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG, "Botão voltar clicado na tela de configuração do relógio");
    lv_scr_load_anim(config_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

static void save_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG, "Botão salvar clicado na tela de configuração do relógio");
    
    // Obter os valores selecionados
    char buf[16];
    int hour, minute, day, month, year;
    
    lv_roller_get_selected_str(hour_roller, buf, sizeof(buf));
    hour = atoi(buf);
    
    lv_roller_get_selected_str(minute_roller, buf, sizeof(buf));
    minute = atoi(buf);
    
    lv_roller_get_selected_str(day_roller, buf, sizeof(buf));
    day = atoi(buf);
    
    lv_roller_get_selected_str(month_roller, buf, sizeof(buf));
    month = atoi(buf);
    
    lv_roller_get_selected_str(year_roller, buf, sizeof(buf));
    year = atoi(buf);
    
    ESP_LOGI(TAG, "Configurando RTC: %02d/%02d/%04d %02d:%02d", day, month, year, hour, minute);
    
    // Atualizar o RTC
    datetime_t new_datetime;
    new_datetime.year = year;
    new_datetime.month = month;
    new_datetime.day = day;
    new_datetime.hour = hour;
    new_datetime.minute = minute;
    new_datetime.second = 0;
    
    // Calcular o dia da semana (0 = domingo, 1 = segunda, ..., 6 = sábado)
    // Algoritmo de Zeller
    int q = day;
    int m = month;
    int y = year;
    
    if (m <= 2) {
        m += 12;
        y -= 1;
    }
    
    int h = (q + (13 * (m + 1)) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    // Ajustar para que domingo seja 0 em vez de 1
    new_datetime.dotw = (h + 6) % 7;
    
    PCF85063_Set_All(new_datetime);
    
    // Voltar para a tela principal
    lv_scr_load_anim(config_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

// Função para carregar a tela de configurações do relógio
void clock_settings_screen_load(void) {
    ESP_LOGI(TAG, "Carregando tela de configurações do relógio");
    
    // Cria a tela de configurações do relógio
    lv_obj_t *scr = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(scr, lv_color_white(), LV_PART_MAIN);
    
    // Título
    lv_obj_t *title = lv_label_create(scr);
    lv_label_set_text(title, "CLOCK SETTINGS");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(title, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

    // Contêiner para controles de tempo
    lv_obj_t *time_container = lv_obj_create(scr);
    lv_obj_set_size(time_container, 200, 130);
    lv_obj_set_style_border_width(time_container, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(time_container, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_align(time_container, LV_ALIGN_TOP_MID, 0, 65);
    
    // Área para os controles de tempo
    lv_obj_t *time_label = lv_label_create(scr);
    lv_label_set_text(time_label, "Hora:");
    lv_obj_set_style_text_font(time_label, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(time_label, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(time_label, LV_ALIGN_TOP_LEFT, 10, 60);
    
    // Criando rollers para hora e minuto
    hour_roller = lv_roller_create(time_container);
    lv_roller_set_options(hour_roller,
                         "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n"
                         "10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n"
                         "20\n21\n22\n23",
                         LV_ROLLER_MODE_NORMAL);
    lv_obj_set_size(hour_roller, 60, 100);
    lv_obj_align(hour_roller, LV_ALIGN_CENTER, -40, 0);
    
    lv_obj_t *time_sep = lv_label_create(time_container);
    lv_label_set_text(time_sep, ":");
    lv_obj_set_style_text_font(time_sep, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(time_sep, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(time_sep, LV_ALIGN_CENTER, 0, 0);
    
    minute_roller = lv_roller_create(time_container);
    lv_roller_set_options(minute_roller,
                         "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n"
                         "10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n"
                         "20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n"
                         "30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n"
                         "40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n"
                         "50\n51\n52\n53\n54\n55\n56\n57\n58\n59",
                         LV_ROLLER_MODE_NORMAL);
    lv_obj_set_size(minute_roller, 60, 100);
    lv_obj_align(minute_roller, LV_ALIGN_CENTER, 40, 0);
    
    // Área para os controles de data
    lv_obj_t *date_label = lv_label_create(scr);
    lv_label_set_text(date_label, "Data:");
    lv_obj_set_style_text_font(date_label, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(date_label, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(date_label, LV_ALIGN_TOP_LEFT, 10, 180);

    // Contêiner para controles de data
    lv_obj_t *date_container = lv_obj_create(scr);
    lv_obj_set_size(date_container, 238, 130);
    lv_obj_set_style_border_width(date_container, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(date_container, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_align(date_container, LV_ALIGN_CENTER, 0, 90);
    
    // Criando rollers para dia, mês e ano
    day_roller = lv_roller_create(date_container);
    lv_roller_set_options(day_roller,
                         "01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n"
                         "11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n"
                         "21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31",
                         LV_ROLLER_MODE_NORMAL);
    lv_obj_set_size(day_roller, 60, 100);
    lv_obj_align(day_roller, LV_ALIGN_CENTER, -80, 0);
    
    lv_obj_t *date_sep1 = lv_label_create(date_container);
    lv_label_set_text(date_sep1, "/");
    lv_obj_set_style_text_font(date_sep1, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(date_sep1, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(date_sep1, LV_ALIGN_CENTER, -40, 0);
    
    month_roller = lv_roller_create(date_container);
    lv_roller_set_options(month_roller,
                         "01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12",
                         LV_ROLLER_MODE_NORMAL);
    lv_obj_set_size(month_roller, 60, 100);
    lv_obj_align(month_roller, LV_ALIGN_CENTER, 0, 0);
    
    lv_obj_t *date_sep2 = lv_label_create(date_container);
    lv_label_set_text(date_sep2, "/");
    lv_obj_set_style_text_font(date_sep2, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(date_sep2, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(date_sep2, LV_ALIGN_CENTER, 40, 0);
    
    year_roller = lv_roller_create(date_container);
    // Anos de 2020 a 2040
    lv_roller_set_options(year_roller,
                         "2025\n2026\n2027\n2028\n2029\n"
                         "2030\n2031\n2032\n2033\n2034\n2035\n2036\n2037\n2038\n2039\n"
                         "2040\n2041\n2042\n2043\n2044\n2045\n2046\n2047\n2048\n2049\n"
                         "2050\n2051\n2052\n2053\n2054\n2055\n2056\n2057\n2058\n2059\n"
                         "2060\n2061\n2062\n2063\n2064\n2065\n2066\n2067\n2068\n2069\n"
                         "2070\n2071\n2072\n2073\n2074\n2075\n2076\n2077\n2078\n2079\n"
                         "2080\n2081\n2082\n2083\n2084\n2085\n2086\n2087\n2088\n2089\n"
                         "2090\n2091\n2092\n2093\n2094\n2095\n2096\n2097\n2098\n2099",
                         LV_ROLLER_MODE_NORMAL);
    lv_obj_set_size(year_roller, 60, 100);
    lv_obj_align(year_roller, LV_ALIGN_CENTER, 80, 0);
    
    // Botão para salvar configurações
    // save_btn = lv_btn_create(scr);
    // lv_obj_set_size(save_btn, 100, 40);
    // lv_obj_align(save_btn, LV_ALIGN_BOTTOM_RIGHT, -20, -20);
    // lv_obj_add_event_cb(save_btn, save_btn_event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t *home_btn = lv_btn_create(scr);
    lv_obj_set_size(home_btn, 40, 40);
    lv_obj_align(home_btn, LV_ALIGN_TOP_LEFT, 5, 5);
    lv_obj_add_event_cb(home_btn, back_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *gear_icon = lv_label_create(home_btn);
    lv_label_set_text(gear_icon, LV_SYMBOL_LEFT);
    lv_obj_center(gear_icon);

    lv_obj_t *save_btn = lv_btn_create(scr);
    lv_obj_set_size(save_btn, 40, 40);
    lv_obj_align(save_btn, LV_ALIGN_TOP_RIGHT, -5, 5);
    lv_obj_add_event_cb(save_btn, save_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *save_icon = lv_label_create(save_btn);
    lv_label_set_text(save_icon, LV_SYMBOL_SAVE);
    lv_obj_center(save_icon);
    
    // lv_obj_t *save_label = lv_label_create(save_btn);
    // lv_label_set_text(save_label, "Salvar");
    // lv_obj_center(save_label);
    
    // // Botão para voltar sem salvar
    // back_btn = lv_btn_create(scr);
    // lv_obj_set_size(back_btn, 100, 40);
    // lv_obj_align(back_btn, LV_ALIGN_BOTTOM_LEFT, 20, -20);
    // lv_obj_add_event_cb(back_btn, back_btn_event_handler, LV_EVENT_CLICKED, NULL);
    
    // lv_obj_t *back_label = lv_label_create(back_btn);
    // lv_label_set_text(back_label, "Voltar");
    // lv_obj_center(back_label);
    
    // Definir os valores atuais nos rollers
    lv_roller_set_selected(hour_roller, datetime.hour, LV_ANIM_OFF);
    lv_roller_set_selected(minute_roller, datetime.minute, LV_ANIM_OFF);
    lv_roller_set_selected(day_roller, datetime.day - 1, LV_ANIM_OFF);  // Ajuste para arrays baseados em zero
    lv_roller_set_selected(month_roller, datetime.month - 1, LV_ANIM_OFF); // Ajuste para arrays baseados em zero
    lv_roller_set_selected(year_roller, datetime.year - 2025, LV_ANIM_OFF); // Ajuste para o ano base 2025
    
    lv_scr_load_anim(scr, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
    // lv_scr_load(scr);
}