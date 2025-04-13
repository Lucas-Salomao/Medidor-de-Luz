#include "Screens.h"
#include "logo.h"
#include "VEML7700.h"

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
static lv_obj_t *lux_label = NULL;

void setup_ui(void) {
    i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = 11,
        .scl_io_num = 10,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,
    };
    i2c_param_config(I2C_NUM_0, &i2c_conf);
    i2c_driver_install(I2C_NUM_0, i2c_conf.mode, 0, 0, 0);

    VEML7700_Init(I2C_NUM_0);

    splash_screen = lv_obj_create(NULL);
    main_screen = lv_obj_create(NULL);
    config_screen = lv_obj_create(NULL);
    
    lv_obj_set_style_bg_color(splash_screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(main_screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(config_screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    create_splash_screen(splash_screen);
    create_main_screen(main_screen);
    create_config_screen(config_screen);
    
    lv_scr_load(splash_screen);
    
    splash_timer = lv_timer_create(splash_timer_callback, 3000, NULL);
    lv_timer_set_repeat_count(splash_timer, 1);
}

void create_splash_screen(lv_obj_t *parent) {
    lv_obj_t *img = lv_img_create(parent);
    lv_img_set_src(img, &splash_image);
    lv_obj_center(img);
}

void create_main_screen(lv_obj_t *parent) {
    lv_obj_t *title = lv_label_create(parent);
    lv_label_set_text(title, "Medidor de Luz");
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
    lv_obj_align(config_btn, LV_ALIGN_TOP_RIGHT, -5, 40);
    lv_obj_add_event_cb(config_btn, config_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *gear_icon = lv_label_create(config_btn);
    lv_label_set_text(gear_icon, LV_SYMBOL_SETTINGS);
    lv_obj_center(gear_icon);
}

void create_config_screen(lv_obj_t *parent) {
    lv_obj_t *title = lv_label_create(parent);
    lv_label_set_text(title, "Wi-Fi Configuration");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *return_btn = lv_btn_create(parent);
    lv_obj_set_size(return_btn, 40, 40);
    lv_obj_align(return_btn, LV_ALIGN_TOP_LEFT, 5, 40);
    lv_obj_add_event_cb(return_btn, return_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *return_icon = lv_label_create(return_btn);
    lv_label_set_text(return_icon, LV_SYMBOL_HOME);
    lv_obj_center(return_icon);
}

void splash_timer_callback(lv_timer_t *timer) {
    lv_scr_load_anim(main_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

void update_lux_value(float lux) {
    char buf[32];
    snprintf(buf, sizeof(buf), "Lux: %.2f", lux);
    lv_label_set_text(lux_label, buf);
}

void config_btn_event_handler(lv_event_t *e) {
    lv_scr_load_anim(config_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

void return_btn_event_handler(lv_event_t *e) {
    lv_scr_load_anim(main_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
}

void sensor_task(void *arg) {
    while (1) {
        float lux;
        if (VEML7700_Read_Lux(&lux) == ESP_OK) {
            update_lux_value(lux);
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}