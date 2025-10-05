#pragma once

#ifndef SETTINGS_SCREEN_H
#define SETTINGS_SCREEN_H

#include "lvgl.h"

void create_config_screen(lv_obj_t *parent);
void settings_language_dropdown_event_handler(lv_event_t *e);
void settings_screen_update_texts(void);

#endif