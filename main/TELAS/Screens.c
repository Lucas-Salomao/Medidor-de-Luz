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
#include "../Languages/internationalization.h"

#define AUDIO_ZERO_PROMPT    "zero_prompt.mp3"

// Definindo as variáveis globais
const char *TAG = "Screens";
lv_obj_t *splash_screen = NULL;
lv_obj_t *main_screen = NULL;
lv_obj_t *config_screen = NULL;
lv_obj_t *clock_config_screen = NULL;
lv_obj_t *wifi_config_screen = NULL;
lv_timer_t *splash_timer = NULL;
lv_obj_t *lux_label = NULL;

// Protótipo da função de criação da tela principal
void create_main_screen(lv_obj_t *parent);

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

void reinit_ui_on_language_change(void) {
    ESP_LOGI(TAG, "Reinicializando a UI para mudança de idioma.");

    // CRÍTICO: Limpa recursos (tasks e timers) do fluorimeter antes de recriar as telas
    cleanup_fluorimeter_resources();

    // Deleta telas auxiliares se existirem (forçará recriação com novo idioma ao navegar)
    if (clock_config_screen) {
        lv_obj_del(clock_config_screen);
        clock_config_screen = NULL;
    }
    if (wifi_config_screen) {
        lv_obj_del(wifi_config_screen);
        wifi_config_screen = NULL;
    }

    // Deleta o timer da splash screen se ele ainda existir
    if (splash_timer) {
        lv_timer_del(splash_timer);
        splash_timer = NULL;
    }

    // Guarda referências das telas antigas para deletar DEPOIS
    lv_obj_t *old_main_screen = main_screen;
    lv_obj_t *old_config_screen = config_screen;

    // Recria as telas principais PRIMEIRO (antes de deletar as antigas)
    main_screen = lv_obj_create(NULL);
    config_screen = lv_obj_create(NULL);

    if (main_screen == NULL || config_screen == NULL) {
        ESP_LOGE(TAG, "Falha ao recriar telas após mudança de idioma");
        // Restaura ponteiros antigos em caso de falha
        main_screen = old_main_screen;
        config_screen = old_config_screen;
        return;
    }

    // Define a cor de fundo para as novas telas
    lv_obj_set_style_bg_color(main_screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(config_screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    // Recria o conteúdo das telas com o novo idioma
    create_main_screen(main_screen);
    create_config_screen(config_screen);

    // Carrega a nova tela de configurações com auto_del=false (não deletar anterior automaticamente)
    // Deletamos manualmente as telas antigas DEPOIS da transição
    lv_scr_load(config_screen);
    
    // Agora é seguro deletar as telas antigas (a nova já está carregada)
    if (old_main_screen) {
        lv_obj_del(old_main_screen);
    }
    if (old_config_screen) {
        lv_obj_del(old_config_screen);
    }
    
    // Deleta splash screen antiga se existir
    if (splash_screen) {
        lv_obj_del(splash_screen);
        splash_screen = NULL;
    }
    
    ESP_LOGI(TAG, "UI reinicializada com sucesso.");
}

void splash_timer_callback(lv_timer_t *timer) {
    ESP_LOGI(TAG, "Carregando tela principal após splash");
    
    // O último parâmetro (true) faz o LVGL deletar a splash_screen automaticamente
    // APÓS a animação terminar, evitando crash por deletar tela ativa
    lv_scr_load_anim(main_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, true);
    splash_screen = NULL;  // Marca como NULL pois será deletada automaticamente
    ESP_LOGI(TAG, "splash_screen será liberada após animação");
    
    // Toca o primeiro áudio aqui, após a tela principal ser carregada
    char audio_dir[64];
    snprintf(audio_dir, sizeof(audio_dir), "/sdcard/%s", get_language_code());
    Play_Music(audio_dir, AUDIO_ZERO_PROMPT);

    // Reseta a flag para permitir que os sons toquem normalmente a partir de agora
    if (is_first_load) {
        is_first_load = false;
    }
    splash_timer = NULL;
}

void reinit_ui_task(lv_timer_t *timer) {
    reinit_ui_on_language_change();
}