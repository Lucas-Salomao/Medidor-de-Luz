#include "Screens.h"
#include "splash_screen.h"
#include "settings_screen.h"
#include "fluorimeter_screen.h"
#include "PCM5101.h"

#include "esp_log.h"
#include "esp_wifi.h"
#include "nvs_flash.h" 
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_sntp.h"
#include "lwip/apps/sntp.h"

// Definindo as variáveis globais
const char *TAG = "Screens";
lv_obj_t *splash_screen = NULL;
lv_obj_t *main_screen = NULL;
lv_obj_t *config_screen = NULL;
lv_obj_t *clock_config_screen = NULL;
lv_obj_t *wifi_config_screen = NULL;
lv_timer_t *splash_timer = NULL;
lv_obj_t *lux_label = NULL;

void setup_ui(void) {
    // ESP_LOGI(TAG, "Inicializando UI");

    splash_screen = lv_obj_create(NULL);
    main_screen = lv_obj_create(NULL);
    config_screen = lv_obj_create(NULL);

    if (splash_screen == NULL || main_screen == NULL || config_screen == NULL) {
        ESP_LOGE(TAG, "Falha ao criar telas");
        return;
    }

    // ESP_LOGI(TAG, "Telas criadas com sucesso");
    
    lv_obj_set_style_bg_color(splash_screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(main_screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(config_screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // ESP_LOGI(TAG, "Criando splash screen");
    create_splash_screen(splash_screen);
    
    // ESP_LOGI(TAG, "Criando main screen");
    create_main_screen(main_screen);
    
    // ESP_LOGI(TAG, "Criando config screen");
    create_config_screen(config_screen);
    
    lv_scr_load(splash_screen);
    
    splash_timer = lv_timer_create(splash_timer_callback, 3000, NULL);
    lv_timer_set_repeat_count(splash_timer, 1);

    ESP_LOGI(TAG, "UI inicializada com sucesso");
}

void splash_timer_callback(lv_timer_t *timer) {
    ESP_LOGI(TAG, "Carregando tela principal após splash");
    lv_scr_load_anim(main_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
    
    // Toca o primeiro áudio aqui, após a tela principal ser carregada
    Play_Music("/sdcard", "zero_prompt.mp3");

    // Reseta a flag para permitir que os sons toquem normalmente a partir de agora
    if (is_first_load) {
        is_first_load = false;
    }
}