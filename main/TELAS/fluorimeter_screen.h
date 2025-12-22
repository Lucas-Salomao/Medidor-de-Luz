#pragma once

#ifndef FLUXIMETER_SCREEN_H
#define FLUXIMETER_SCREEN_H

extern bool is_first_load;
extern bool skip_audio_on_reinit;  // Flag para pular áudio durante reinicialização da UI

// Função para limpar recursos do fluorimeter antes de reinicializar a UI
void cleanup_fluorimeter_resources(void);

void config_btn_event_handler(lv_event_t *e);
void create_main_screen(lv_obj_t *parent);

#endif