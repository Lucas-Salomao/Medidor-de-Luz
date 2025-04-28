#include "lvgl.h"
#include "logo.h" // Para carregar o logo

// Declaração da imagem do logo (definida em logo.c)
// extern const lv_img_dsc_t logo_scintilum;

// Função de callback para animar a barra de progresso
static void bar_anim_cb(void *var, int32_t value) {
    lv_bar_set_value((lv_obj_t *)var, value, LV_ANIM_ON);
}

// Função para carregar a tela de abertura
void create_splash_screen(lv_obj_t *parent) {
    lv_obj_set_style_bg_color(parent, lv_color_white(), LV_PART_MAIN);

    // Adiciona o logo centralizado
    lv_obj_t *img = lv_img_create(parent);
    lv_img_set_src(img, &logo_scintilum);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, -20); // Levemente acima do centro

    // Cria a barra de progresso
    lv_obj_t *bar = lv_bar_create(parent);
    lv_obj_set_size(bar, 200, 20);
    lv_obj_align(bar, LV_ALIGN_BOTTOM_MID, 0, -20); // Abaixo do logo
    lv_bar_set_range(bar, 0, 100);
    lv_bar_set_value(bar, 0, LV_ANIM_OFF);

    // Estiliza a barra de progresso
    static lv_style_t style_bar;
    lv_style_init(&style_bar);
    lv_style_set_bg_color(&style_bar, lv_color_make(0xE0, 0xE0, 0xE0)); // Fundo cinza claro
    lv_obj_add_style(bar, &style_bar, LV_PART_MAIN);

    static lv_style_t style_indic;
    lv_style_init(&style_indic);
    lv_style_set_bg_color(&style_indic, lv_color_make(0x00, 0x80, 0xFF)); // Indicador azul
    lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);

    // Cria a animação da barra (0 a 100 em 3 segundos)
    lv_anim_t anim;
    lv_anim_init(&anim);
    lv_anim_set_var(&anim, bar);
    lv_anim_set_values(&anim, 0, 100);
    lv_anim_set_time(&anim, 3000); // 3 segundos
    lv_anim_set_exec_cb(&anim, bar_anim_cb);
    lv_anim_set_path_cb(&anim, lv_anim_path_linear); // Progressão linear
    lv_anim_start(&anim);
}