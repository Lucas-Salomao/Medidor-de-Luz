#include "lvgl.h"
#include "wifi_settings_screen.h"
#include "Wireless.h"
#include "esp_log.h"
#include "Screens.h"
#include "PCM5101.h"
#include "internationalization.h"
#include "Fonts/custom_fonts.h"

static lv_obj_t *wifi_screen = NULL;
static lv_obj_t *ssid_dropdown = NULL;
static lv_obj_t *password_input = NULL;
static lv_obj_t *status_label = NULL;
static lv_obj_t *keyboard = NULL; // Objeto do teclado

// Forward declarations
static void back_btn_event_handler(lv_event_t *e);
static void connect_btn_event_handler(lv_event_t *e);
static void refresh_btn_event_handler(lv_event_t *e);
static void populate_wifi_dropdown(void *data);
static void password_input_event_handler(lv_event_t *e);
static void screen_click_event_handler(lv_event_t *e);
static void keyboard_close_handler(lv_event_t *e);  

void wifi_settings_screen_init(void) {
    if (wifi_screen == NULL) {
        wifi_screen = lv_obj_create(NULL);
        lv_obj_set_style_bg_color(wifi_screen, lv_color_white(), LV_PART_MAIN);

        // Adiciona evento de clique na tela para fechar o teclado
        lv_obj_add_event_cb(wifi_screen, screen_click_event_handler, LV_EVENT_CLICKED, NULL);
        
        // Title
        lv_obj_t *title = lv_label_create(wifi_screen);
        lv_label_set_text(title, get_string(STRING_WIFI_SETTINGS));
        lv_obj_set_style_text_font(title, &montserrat_pt_16, 0);
        lv_obj_set_style_text_color(title, lv_color_black(), LV_PART_MAIN);
        lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);
        
        // Back button
        lv_obj_t *home_btn = lv_btn_create(wifi_screen);
        lv_obj_set_size(home_btn, 40, 40);
        lv_obj_align(home_btn, LV_ALIGN_TOP_LEFT, 5, 5);
        lv_obj_add_event_cb(home_btn, back_btn_event_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_t *gear_icon = lv_label_create(home_btn);
        lv_label_set_text(gear_icon, LV_SYMBOL_LEFT);
        lv_obj_center(gear_icon);
        
        // SSID Label
        lv_obj_t *ssid_label = lv_label_create(wifi_screen);
        lv_label_set_text(ssid_label, get_string(STRING_NETWORK_SSID));
        lv_obj_set_style_text_color(ssid_label, lv_color_black(), LV_PART_MAIN);
        lv_obj_align(ssid_label, LV_ALIGN_TOP_LEFT, 20, 60);
        
        // SSID Dropdown
        ssid_dropdown = lv_dropdown_create(wifi_screen);
        lv_obj_set_size(ssid_dropdown, 200, 40);
        lv_obj_align(ssid_dropdown, LV_ALIGN_TOP_LEFT, 20, 80);
        
        // Refresh button
        lv_obj_t *refresh_btn = lv_btn_create(wifi_screen);
        lv_obj_set_size(refresh_btn, 40, 40);
        lv_obj_align(refresh_btn, LV_ALIGN_TOP_RIGHT, -5, 5);
        lv_obj_add_event_cb(refresh_btn, refresh_btn_event_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_t *refresh_icon = lv_label_create(refresh_btn);
        lv_label_set_text(refresh_icon, LV_SYMBOL_REFRESH);
        lv_obj_center(refresh_icon);
        
        // Password Label
        lv_obj_t *pwd_label = lv_label_create(wifi_screen);
        lv_label_set_text(pwd_label, get_string(STRING_PASSWORD));
        lv_obj_set_style_text_color(pwd_label, lv_color_black(), LV_PART_MAIN);
        lv_obj_align(pwd_label, LV_ALIGN_TOP_LEFT, 20, 130);
        
        // Password Input
        password_input = lv_textarea_create(wifi_screen);
        lv_textarea_set_password_mode(password_input, false);
        lv_textarea_set_one_line(password_input, true);
        lv_obj_set_size(password_input, 200, 40);
        lv_obj_align(password_input, LV_ALIGN_TOP_LEFT, 20, 155);
        lv_obj_add_event_cb(password_input, password_input_event_handler, LV_EVENT_CLICKED, NULL);
        
        // Connect Button
        lv_obj_t *connect_btn = lv_btn_create(wifi_screen);
        lv_obj_set_size(connect_btn, 200, 50);
        lv_obj_align(connect_btn, LV_ALIGN_TOP_LEFT, 20, 210);
        lv_obj_add_event_cb(connect_btn, connect_btn_event_handler, LV_EVENT_CLICKED, NULL);
        
        lv_obj_t *connect_label = lv_label_create(connect_btn);
        lv_label_set_text(connect_label, get_string(STRING_CONNECT));
        lv_obj_center(connect_label);
        
        // Status label (for connection status/error messages)
        status_label = lv_label_create(wifi_screen);
        lv_label_set_text(status_label, "");
        lv_obj_set_style_text_color(status_label, lv_color_black(), LV_PART_MAIN);
        lv_obj_align(status_label, LV_ALIGN_BOTTOM_MID, 0, -10);

        // Inicializa o teclado
        keyboard = lv_keyboard_create(wifi_screen);
        lv_obj_set_size(keyboard, 240, 120); // Ajusta para 240px de largura e 120px de altura
        lv_obj_align(keyboard, LV_ALIGN_BOTTOM_MID, 0, 0); // Posiciona na parte inferior
        lv_keyboard_set_textarea(keyboard, password_input); // Vincula ao password_input
        lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN); // Esconde o teclado inicialmente
        lv_keyboard_set_mode(keyboard, LV_KEYBOARD_MODE_TEXT_LOWER); // Modo de texto
        // Adiciona evento para fechar o teclado ao pressionar "OK"
        lv_obj_add_event_cb(keyboard, keyboard_close_handler, LV_EVENT_READY, NULL);
        
        // Populate dropdown with dummy values initially
        lv_dropdown_set_options(ssid_dropdown, get_string(STRING_SCANNING));
    }
}

void wifi_settings_screen_load(void) {
    if (wifi_screen == NULL) {
        wifi_settings_screen_init();
    }
    
    lv_scr_load_anim(wifi_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
    
}

static void back_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG, "Back button clicked");
    if (config_screen != NULL) {
        lv_scr_load_anim(config_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
    }
}

static void connect_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG, "Connect button clicked");

    // Exibe mensagem de tentativa de conexão
    lv_label_set_text(status_label, get_string(STRING_CONNECTING));
    lv_obj_set_style_text_color(status_label, lv_color_make(0, 0, 255), LV_PART_MAIN); // Azul para indicar progresso
    
    char selected_ssid[64];
    char password[64];
    
    // Get selected SSID
    uint16_t selected_id = lv_dropdown_get_selected(ssid_dropdown);
    lv_dropdown_get_selected_str(ssid_dropdown, selected_ssid, sizeof(selected_ssid));
    
    // Get password
    const char *pwd_text = lv_textarea_get_text(password_input);
    strncpy(password, pwd_text, sizeof(password) - 1);
    password[sizeof(password) - 1] = '\0';

    // Define as credenciais globais
    WIFI_Set_Credentials(selected_ssid, password);
    
    ESP_LOGI(TAG, "Connecting to SSID: %s with password: %s", selected_ssid, password);
    
    // Tenta conectar
    bool connected = WIFI_Connect(selected_ssid, password);

    // Get language path for audio
    const char* lang_code = get_language_code();
    char lang_dir[20];
    snprintf(lang_dir, sizeof(lang_dir), "/sdcard/%s", lang_code);

    if (connected) {
        lv_label_set_text(status_label, get_string(STRING_CONNECTED_SUCCESSFULLY));
        lv_obj_set_style_text_color(status_label, lv_color_make(0, 128, 0), LV_PART_MAIN); // Verde
        Play_Music(lang_dir, "wifi_connected.mp3");
    } else {
        lv_label_set_text(status_label, get_string(STRING_CONNECTION_FAILED));
        lv_obj_set_style_text_color(status_label, lv_color_make(255, 0, 0), LV_PART_MAIN); // Vermelho
        Play_Music(lang_dir, "wifi_error.mp3");
    }
}

static void refresh_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG, "Refresh button clicked");
    
    // Show scanning message
    lv_dropdown_set_options(ssid_dropdown, get_string(STRING_SCANNING));
    lv_label_set_text(status_label, get_string(STRING_SCANNING_FOR_NETWORKS));
    lv_obj_set_style_text_color(status_label, lv_color_black(), LV_PART_MAIN);
    
    // Start Wi-Fi scan in a separate task
    // This is a simplified example, you should adapt it to your application
    xTaskCreate(
        scan_wifi_task,
        "wifi_scan_task",
        4096,
        NULL,
        5,
        NULL
    );
}

// Task to scan for Wi-Fi networks
static void scan_wifi_task(void *pvParameters) {
    // Realiza o escaneamento
    WIFI_Scan();

    // Atualiza a interface no thread principal do LVGL
    lv_async_call(populate_wifi_dropdown, NULL);

    vTaskDelete(NULL);
}

static void populate_wifi_dropdown(void *data) {
    // Limpa a mensagem de status
    lv_label_set_text(status_label, "");

    // Verifica se foram encontradas redes
    if (WIFI_NUM == 0) {
        lv_dropdown_set_options(ssid_dropdown, get_string(STRING_NO_NETWORKS_FOUND));
        lv_label_set_text(status_label, get_string(STRING_NO_NETWORKS_DETECTED));
        return;
    }

    // Aloca um buffer para as opções do dropdown
    char *buffer = malloc(WIFI_NUM * 34 + 1); // 33 chars por SSID + \n
    if (buffer == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for dropdown options");
        lv_label_set_text(status_label, get_string(STRING_MEMORY_ERROR));
        return;
    }

    buffer[0] = '\0'; // Inicializa string vazia

    // Preenche o buffer com os SSIDs
    for (int i = 0; i < WIFI_NUM; i++) {
        if (i > 0) {
            strcat(buffer, "\n");
        }
        strcat(buffer, wifi_aps[i].ssid);
    }

    // Atualiza as opções do dropdown
    lv_dropdown_set_options(ssid_dropdown, buffer);

    // Libera o buffer
    free(buffer);

    ESP_LOGI(TAG, "Populated dropdown with %d networks", WIFI_NUM);
}

static void password_input_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG, "Password input clicked");
    // Mostra o teclado
    if (keyboard != NULL) {
        lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
        lv_keyboard_set_textarea(keyboard, password_input);
    }
}

static void screen_click_event_handler(lv_event_t *e) {
    // Fecha o teclado se o clique for fora do password_input
    lv_obj_t *target = lv_event_get_target(e);
    if (target != password_input && keyboard != NULL && !lv_obj_has_flag(keyboard, LV_OBJ_FLAG_HIDDEN)) {
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