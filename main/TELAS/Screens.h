#ifndef SCREENS_H
#define SCREENS_H

#include "lvgl.h"

void setup_ui(void);
void create_splash_screen(lv_obj_t *parent);
void create_main_screen(lv_obj_t *parent);
void create_config_screen(lv_obj_t *parent);
void splash_timer_callback(lv_timer_t *timer);
void update_lux_value(float lux); // Nova função para atualizar o valor na tela
void sensor_task(void *arg);
void config_btn_event_handler(lv_event_t *e);
void return_btn_event_handler(lv_event_t *e);

#endif