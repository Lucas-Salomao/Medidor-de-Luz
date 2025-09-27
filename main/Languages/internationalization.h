#ifndef INTERNATIONALIZATION_H
#define INTERNATIONALIZATION_H

#include "stdint.h"

typedef enum {
    LANG_EN,
    LANG_ES,
    LANG_PT_BR,
} language_t;

typedef enum {
    STRING_CLOCK_SETTINGS,
    STRING_WIFI_SETTINGS,
    STRING_FLUORIMETER,
    STRING_SETTINGS,
    STRING_ZEROING_PROMPT,
    STRING_MEASURE_PROMPT,
    STRING_SHOW_RESULT,
    STRING_ZERO,
    STRING_MEASURE,
    STRING_SAVE,
    STRING_REPEAT,
    STRING_SAVED,
    STRING_ID_CANNOT_BE_EMPTY,
    STRING_SD_CARD_ERROR,
    STRING_ENTER_SAMPLE_ID,
    STRING_ID,
    STRING_CONNECTING,
    STRING_CONNECTED_SUCCESSFULLY,
    STRING_CONNECTION_FAILED,
    STRING_SCANNING_FOR_NETWORKS,
    STRING_NO_NETWORKS_FOUND,
    STRING_MEMORY_ERROR,
    STRING_NETWORK_SSID,
    STRING_PASSWORD,
    STRING_CONNECT,
    STRING_SCANNING,
    STRING_NO_NETWORKS_DETECTED,
    STRING_LANGUAGE,
    // Adicione mais IDs de string aqui conforme necessário
} string_id_t;

void set_language(language_t language);
language_t get_language(void);
const char* get_string(string_id_t id);
const char* get_language_code(void);

#endif // INTERNATIONALIZATION_H