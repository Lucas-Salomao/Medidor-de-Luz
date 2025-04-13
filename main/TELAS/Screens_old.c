#include "Screens.h"
#include "logo.h"
#include "VEML7700.h"
#include "Wireless.h"

#include "esp_log.h"
#include "esp_wifi.h"
#include "nvs_flash.h" 
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_sntp.h"
#include "lwip/apps/sntp.h"

static const char *TAG = "Screens";

// Objetos globais
static lv_obj_t *splash_screen = NULL;
static lv_obj_t *main_screen = NULL;
static lv_obj_t *config_screen = NULL;

static lv_timer_t *splash_timer = NULL;
static lv_obj_t *lux_label = NULL; // Label para exibir o valor de lux
static lv_obj_t *wifi_status_label = NULL;
static lv_obj_t *wifi_dropdown = NULL;
static lv_obj_t *password_input = NULL;
static lv_obj_t *keyboard = NULL; // Teclado global

// Variáveis para Wi-Fi
static wifi_ap_record_t *wifi_ap_list = NULL;
static uint16_t wifi_ap_count = 0;
static bool wifi_connected = false;

/**
 * Função principal para inicializar e criar as telas
 */
void setup_ui(void) {

    // Inicializa o I2C
    i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = 11,  // SDA no GPIO 11
        .scl_io_num = 10,  // SCL no GPIO 10
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000, // 100 kHz
    };
    i2c_param_config(I2C_NUM_0, &i2c_conf);
    i2c_driver_install(I2C_NUM_0, i2c_conf.mode, 0, 0, 0);

    // Inicializa o VEML7700
    VEML7700_Init(I2C_NUM_0);

    // Inicializa o TSL2561
    // TSL2561_Init(I2C_NUM_0);

    // Cria as telas
    splash_screen = lv_obj_create(NULL);
    main_screen = lv_obj_create(NULL);
    config_screen = lv_obj_create(NULL);
    
    // Configura o estilo das telas (fundo branco para ambas)
    lv_obj_set_style_bg_color(splash_screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(main_screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(config_screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Cria os elementos das telas
    create_splash_screen(splash_screen);
    create_main_screen(main_screen);
    create_config_screen(config_screen);
    
    // Carrega a tela de splash primeiro
    lv_scr_load(splash_screen);
    
    // Cria um timer para mudar para a tela principal após 3 segundos
    splash_timer = lv_timer_create(splash_timer_callback, 3000, NULL);
    lv_timer_set_repeat_count(splash_timer, 1); // Executa apenas uma vez

    // Criar o teclado (inicialmente escondido)
    keyboard = lv_keyboard_create(lv_scr_act());
    lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN); // Esconder por padrão
}

/**
 * Cria a tela de inicialização (splash) com imagem centralizada
 */
void create_splash_screen(lv_obj_t *parent) {
    // Criar objeto de imagem
    lv_obj_t *img = lv_img_create(parent);
    
    // Definir a imagem a partir da array
    lv_img_set_src(img, &splash_image);
    
    // Centralizar a imagem
    lv_obj_center(img);
}

/**
 * Cria a tela principal com título "Medidor de Luz"
 */
void create_main_screen(lv_obj_t *parent) {
    // Título da tela
    lv_obj_t *title = lv_label_create(parent);
    lv_label_set_text(title, "Medidor de Luz");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(title, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

    // Label para o valor de lux
    lux_label = lv_label_create(parent);
    lv_label_set_text(lux_label, "Lux: --");
    lv_obj_set_style_text_font(lux_label, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(lux_label, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(lux_label, LV_ALIGN_CENTER, 0, 0);

    wifi_status_label = lv_label_create(parent);
    lv_label_set_text(wifi_status_label, "Wi-Fi: Desconectado");
    lv_obj_set_style_text_font(wifi_status_label, &lv_font_montserrat_14, 0);
    lv_obj_align(wifi_status_label, LV_ALIGN_BOTTOM_MID, 0, -10);

    lv_obj_t *config_btn = lv_btn_create(parent);
    lv_obj_set_size(config_btn, 40, 40);
    lv_obj_align(config_btn, LV_ALIGN_TOP_RIGHT, -10, 10);
    lv_obj_add_event_cb(config_btn, config_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *gear_icon = lv_label_create(config_btn);
    lv_label_set_text(gear_icon, LV_SYMBOL_SETTINGS); // Ícone de engrenagem
    lv_obj_center(gear_icon);
}

// Função para abrir o teclado quando o campo de senha é clicado
static void password_input_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(keyboard, password_input);
        lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_HIDDEN); // Mostrar o teclado
    }
}

void create_config_screen(lv_obj_t *parent) {
    lv_obj_t *title = lv_label_create(parent);
    lv_label_set_text(title, "Configuração Wi-Fi");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

    wifi_dropdown = lv_dropdown_create(parent);
    lv_dropdown_set_options(wifi_dropdown, "Escaneando...");
    lv_obj_set_width(wifi_dropdown, 200);
    lv_obj_align(wifi_dropdown, LV_ALIGN_CENTER, 0, -20);

    password_input = lv_textarea_create(parent);
    lv_textarea_set_placeholder_text(password_input, "Senha");
    lv_textarea_set_one_line(password_input, true);
    lv_obj_set_width(password_input, 200);
    lv_obj_align(password_input, LV_ALIGN_CENTER, 0, 20);
    lv_obj_add_event_cb(password_input, password_input_event_handler, LV_EVENT_ALL, NULL); // Evento para abrir o teclado

    lv_obj_t *connect_btn = lv_btn_create(parent);
    lv_obj_set_size(connect_btn, 100, 40);
    lv_obj_align(connect_btn, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_add_event_cb(connect_btn, connect_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *connect_label = lv_label_create(connect_btn);
    lv_label_set_text(connect_label, "Conectar");
    lv_obj_center(connect_label);
}

void config_btn_event_handler(lv_event_t *e) {
    lv_scr_load_anim(config_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);

    wifi_ap_count = WIFI_Scan();
    if (wifi_ap_count > 0) {
        wifi_ap_list = (wifi_ap_record_t *)malloc(wifi_ap_count * sizeof(wifi_ap_record_t));
        esp_wifi_scan_get_ap_records(&wifi_ap_count, wifi_ap_list);

        char options[512] = {0};
        for (int i = 0; i < wifi_ap_count; i++) {
            size_t ssid_len = strlen((char *)wifi_ap_list[i].ssid);
            strncat(options, (char *)wifi_ap_list[i].ssid, ssid_len); // Usa o tamanho real do SSID
            if (i < wifi_ap_count - 1) strncat(options, "\n", 2);
        }
        lv_dropdown_set_options(wifi_dropdown, options);
        free(wifi_ap_list);
    }
}

static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        wifi_connected = false;
        update_wifi_status(false, "--:--:--");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        wifi_connected = true;
        sntp_setoperatingmode(SNTP_OPMODE_POLL);
        sntp_setservername(0, "pool.ntp.org");
        sntp_init();
    }
}

static void time_sync_notification_cb(struct timeval *tv) {
    time_t now;
    struct tm timeinfo;
    char strftime_buf[64];
    time(&now);
    localtime_r(&now, &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf), "%H:%M:%S", &timeinfo);
    update_wifi_status(true, strftime_buf);
}

void connect_btn_event_handler(lv_event_t *e) {
    char ssid[32];
    lv_dropdown_get_selected_str(wifi_dropdown, ssid, sizeof(ssid)); // Buffer para o SSID
    const char *password = lv_textarea_get_text(password_input);

    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, &instance_any_id);
    esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, &instance_got_ip);

    wifi_config_t wifi_config = {0};
    strncpy((char *)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid) - 1);
    strncpy((char *)wifi_config.sta.password, password, sizeof(wifi_config.sta.password) - 1);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    esp_wifi_start();

    sntp_set_time_sync_notification_cb(time_sync_notification_cb);
}

void update_wifi_status(bool connected, const char *time_str) {
    char buf[64];
    snprintf(buf, sizeof(buf), "Wi-Fi: %s | Hora: %s", connected ? "Conectado" : "Desconectado", time_str);
    lv_label_set_text(wifi_status_label, buf);
}

/**
 * Callback do timer para mudar da tela splash para a tela principal
 */
void splash_timer_callback(lv_timer_t *timer) {
    lv_scr_load_anim(main_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

void update_lux_value(float lux) {
    char buf[32];
    snprintf(buf, sizeof(buf), "Lux: %.2f", lux);
    lv_label_set_text(lux_label, buf);
}

//Tarefa para leitura do sensor
void sensor_task(void *arg) {
    while (1) {
        float lux;
        if (VEML7700_Read_Lux(&lux) == ESP_OK) {
            update_lux_value(lux);
        }
        vTaskDelay(pdMS_TO_TICKS(500)); // Atualiza a cada 500ms
    }
}

// void sensor_task(void *arg) {
//     while (1) {
//         float lux;
//         if (TSL2561_Read_Lux(&lux) == ESP_OK) {
//             update_lux_value(lux);
//         }
//         vTaskDelay(pdMS_TO_TICKS(500)); // Atualiza a cada 500ms
//     }
// }