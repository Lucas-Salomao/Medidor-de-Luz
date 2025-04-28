#pragma once

#ifndef SCREENS_H
#define SCREENS_H

#include "lvgl.h"

// Objetos globais
extern const char *TAG;
extern lv_obj_t *splash_screen;
extern lv_obj_t *main_screen;
extern lv_obj_t *config_screen;
extern lv_obj_t *clock_config_screen;
extern lv_obj_t *wifi_config_screen;
extern lv_timer_t *splash_timer;
extern lv_obj_t *lux_label;

void setup_ui(void);
void splash_timer_callback(lv_timer_t *timer);

#endif