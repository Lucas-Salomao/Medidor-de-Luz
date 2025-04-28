#pragma once

#ifndef WIFI_SETTINGS_SCREEN_H
#define WIFI_SETTINGS_SCREEN_H

#include "lvgl.h"

static void scan_wifi_task(void *pvParameters);
void wifi_settings_screen_load(void);
void wifi_settings_screen_init(void);

#endif /* WIFI_SETTINGS_SCREEN_H */