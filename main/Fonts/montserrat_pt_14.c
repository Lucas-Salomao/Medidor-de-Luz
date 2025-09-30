/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --no-compress --stride 1 --align 1 --font Montserrat-Light.ttf --symbols 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáàâãéêíóôõúçÁÀÂÃÉÊÍÓÔÕÚÇ !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~°ªº --format lvgl -o montserrat_pt_14.c
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif



#ifndef MONTSERRAT_PT_14
#define MONTSERRAT_PT_14 1
#endif

#if MONTSERRAT_PT_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfc, 0x80,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x12, 0x9, 0x1f, 0xe4, 0x42, 0x21, 0x13, 0xfe,
    0x44, 0x24, 0x0,

    /* U+0024 "$" */
    0x10, 0x21, 0xf4, 0x89, 0x1a, 0xe, 0xb, 0x12,
    0x27, 0xf0, 0x81, 0x0,

    /* U+0025 "%" */
    0x70, 0x22, 0xc8, 0xa2, 0x30, 0x29, 0x82, 0x91,
    0x24, 0x89, 0x21, 0x80,

    /* U+0026 "&" */
    0x38, 0x44, 0x44, 0x38, 0x30, 0xc9, 0x86, 0x82,
    0x7d, 0x0,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x49, 0x49, 0x24, 0x91, 0x24,

    /* U+0029 ")" */
    0x89, 0x12, 0x49, 0x25, 0x28,

    /* U+002A "*" */
    0x25, 0x5d, 0x52, 0x0,

    /* U+002B "+" */
    0x10, 0x23, 0xf8, 0x81, 0x0,

    /* U+002C "," */
    0xe0,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x8, 0x44, 0x22, 0x10, 0x88, 0x42, 0x21, 0x8,
    0x0,

    /* U+0030 "0" */
    0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x81, 0x42,
    0x3c,

    /* U+0031 "1" */
    0xe4, 0x92, 0x49, 0x20,

    /* U+0032 "2" */
    0x7c, 0x4, 0x8, 0x10, 0x41, 0x4, 0x10, 0x7e,

    /* U+0033 "3" */
    0xfc, 0x10, 0x41, 0xc0, 0x60, 0x40, 0xc1, 0x7c,

    /* U+0034 "4" */
    0x4, 0x4, 0x2, 0x2, 0x2, 0x22, 0x13, 0xfe,
    0x4, 0x2, 0x0,

    /* U+0035 "5" */
    0x7d, 0x2, 0x3, 0xc0, 0x60, 0x40, 0xc1, 0x7c,

    /* U+0036 "6" */
    0x3c, 0x82, 0x4, 0xce, 0x70, 0x60, 0xa1, 0x3c,

    /* U+0037 "7" */
    0xff, 0x4, 0x10, 0x20, 0x81, 0x4, 0x8, 0x20,

    /* U+0038 "8" */
    0x7c, 0x82, 0x82, 0x82, 0x7c, 0xc3, 0x81, 0x81,
    0x7e,

    /* U+0039 "9" */
    0x79, 0xa, 0xc, 0x17, 0xe0, 0x40, 0x82, 0x78,

    /* U+003A ":" */
    0x82,

    /* U+003B ";" */
    0x83, 0x80,

    /* U+003C "<" */
    0xd, 0xc8, 0x1c, 0xc,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0xc0, 0xe0, 0x4e, 0xc0,

    /* U+003F "?" */
    0x7c, 0x4, 0x8, 0x30, 0x82, 0x0, 0x0, 0x10,

    /* U+0040 "@" */
    0xf, 0x81, 0x83, 0x11, 0xd5, 0x11, 0x99, 0x4,
    0xc8, 0x26, 0x41, 0x31, 0x19, 0xc7, 0x72, 0x0,
    0x8, 0x0, 0x3f, 0x0,

    /* U+0041 "A" */
    0xc, 0x3, 0x1, 0x20, 0x48, 0x21, 0x8, 0x47,
    0xf9, 0x2, 0x80, 0x40,

    /* U+0042 "B" */
    0xfe, 0x81, 0x81, 0x81, 0xfe, 0x83, 0x81, 0x81,
    0xfe,

    /* U+0043 "C" */
    0x1f, 0x30, 0x50, 0x10, 0x8, 0x4, 0x1, 0x0,
    0xc1, 0x1f, 0x0,

    /* U+0044 "D" */
    0xfc, 0x41, 0xa0, 0x50, 0x18, 0xc, 0x6, 0x7,
    0x2, 0xfe, 0x0,

    /* U+0045 "E" */
    0xff, 0x2, 0x4, 0xf, 0xd0, 0x20, 0x40, 0xfe,

    /* U+0046 "F" */
    0xff, 0x2, 0x4, 0xf, 0xd0, 0x20, 0x40, 0x80,

    /* U+0047 "G" */
    0x1f, 0x30, 0x50, 0x10, 0x8, 0x4, 0x5, 0x2,
    0xc1, 0x1f, 0x0,

    /* U+0048 "H" */
    0x81, 0x81, 0x81, 0x81, 0xff, 0x81, 0x81, 0x81,
    0x81,

    /* U+0049 "I" */
    0xff, 0x80,

    /* U+004A "J" */
    0x7c, 0x10, 0x41, 0x4, 0x10, 0x41, 0x78,

    /* U+004B "K" */
    0x82, 0x84, 0x88, 0x90, 0xb0, 0xc8, 0x84, 0x82,
    0x81,

    /* U+004C "L" */
    0x81, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0xfe,

    /* U+004D "M" */
    0x80, 0x70, 0x3c, 0x16, 0x85, 0x92, 0x64, 0x98,
    0xc6, 0x1, 0x80, 0x40,

    /* U+004E "N" */
    0x81, 0xc1, 0xa1, 0x91, 0x91, 0x89, 0x85, 0x83,
    0x81,

    /* U+004F "O" */
    0x1e, 0x18, 0x6c, 0xa, 0x1, 0x80, 0x60, 0x1c,
    0xd, 0x2, 0x3f, 0x0,

    /* U+0050 "P" */
    0xfc, 0x83, 0x81, 0x81, 0x82, 0xfc, 0x80, 0x80,
    0x80,

    /* U+0051 "Q" */
    0x1e, 0x18, 0x6c, 0xa, 0x1, 0x80, 0x60, 0x1c,
    0xd, 0x2, 0x3f, 0x1, 0x0, 0x3c,

    /* U+0052 "R" */
    0xfc, 0x83, 0x81, 0x81, 0x82, 0xfc, 0x84, 0x82,
    0x81,

    /* U+0053 "S" */
    0x7d, 0x2, 0x6, 0x3, 0x80, 0xc0, 0x81, 0xfc,

    /* U+0054 "T" */
    0xff, 0x84, 0x2, 0x1, 0x0, 0x80, 0x40, 0x20,
    0x10, 0x8, 0x0,

    /* U+0055 "U" */
    0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x42,
    0x3c,

    /* U+0056 "V" */
    0x80, 0x90, 0x24, 0x10, 0x84, 0x22, 0x4, 0x81,
    0x40, 0x30, 0x8, 0x0,

    /* U+0057 "W" */
    0x82, 0x6, 0x14, 0x28, 0x50, 0x91, 0x42, 0x48,
    0x91, 0x22, 0x42, 0x8a, 0xc, 0x18, 0x10, 0x20,

    /* U+0058 "X" */
    0x41, 0x11, 0x9, 0x2, 0x80, 0x80, 0xa0, 0x88,
    0x84, 0x41, 0x0,

    /* U+0059 "Y" */
    0x80, 0xa0, 0x88, 0x84, 0x41, 0x40, 0x40, 0x20,
    0x10, 0x8, 0x0,

    /* U+005A "Z" */
    0xff, 0x2, 0x4, 0x8, 0x10, 0x10, 0x20, 0x40,
    0xff,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x4e,

    /* U+005C "\\" */
    0x4, 0x21, 0x4, 0x21, 0x4, 0x20, 0x84, 0x20,
    0x80,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x9e,

    /* U+005E "^" */
    0x0, 0xc5, 0x12, 0x4a, 0x10,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0x88,

    /* U+0061 "a" */
    0x78, 0x10, 0x5f, 0x86, 0x17, 0xc0,

    /* U+0062 "b" */
    0x81, 0x2, 0x5, 0xcc, 0x50, 0x60, 0xc1, 0xc5,
    0x70,

    /* U+0063 "c" */
    0x3c, 0x82, 0x4, 0x8, 0x8, 0xf, 0x0,

    /* U+0064 "d" */
    0x2, 0x4, 0x9, 0xd4, 0x70, 0x60, 0xc1, 0x46,
    0x74,

    /* U+0065 "e" */
    0x38, 0x8a, 0xf, 0xf8, 0x8, 0xf, 0x0,

    /* U+0066 "f" */
    0x3a, 0x11, 0xe4, 0x21, 0x8, 0x42, 0x0,

    /* U+0067 "g" */
    0x3d, 0x43, 0x81, 0x81, 0x81, 0x43, 0x3d, 0x1,
    0x3, 0x7e,

    /* U+0068 "h" */
    0x81, 0x2, 0x5, 0xec, 0x30, 0x60, 0xc1, 0x83,
    0x4,

    /* U+0069 "i" */
    0x9f, 0xc0,

    /* U+006A "j" */
    0x10, 0x1, 0x11, 0x11, 0x11, 0x11, 0xe0,

    /* U+006B "k" */
    0x81, 0x2, 0x4, 0x28, 0x92, 0x3c, 0x44, 0x85,
    0x8,

    /* U+006C "l" */
    0xff, 0xc0,

    /* U+006D "m" */
    0xbc, 0xf6, 0x18, 0x60, 0x83, 0x4, 0x18, 0x20,
    0xc1, 0x6, 0x8, 0x20,

    /* U+006E "n" */
    0xbd, 0x86, 0xc, 0x18, 0x30, 0x60, 0x80,

    /* U+006F "o" */
    0x38, 0x8a, 0xc, 0x18, 0x28, 0x8e, 0x0,

    /* U+0070 "p" */
    0xb9, 0x8a, 0xc, 0x18, 0x38, 0xae, 0x40, 0x81,
    0x0,

    /* U+0071 "q" */
    0x3a, 0x8e, 0xc, 0x18, 0x28, 0xce, 0x81, 0x2,
    0x4,

    /* U+0072 "r" */
    0xbc, 0x88, 0x88, 0x80,

    /* U+0073 "s" */
    0x7a, 0x8, 0x1c, 0xc, 0x1f, 0x80,

    /* U+0074 "t" */
    0x42, 0x3c, 0x84, 0x21, 0x8, 0x38,

    /* U+0075 "u" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0xde, 0x80,

    /* U+0076 "v" */
    0x83, 0x5, 0x12, 0x22, 0x85, 0x4, 0x0,

    /* U+0077 "w" */
    0x82, 0x18, 0x62, 0x4a, 0x24, 0x92, 0x29, 0x43,
    0xc, 0x10, 0x80,

    /* U+0078 "x" */
    0x44, 0xc8, 0xa0, 0x82, 0x88, 0x90, 0x80,

    /* U+0079 "y" */
    0x83, 0x5, 0x12, 0x22, 0x85, 0x4, 0x8, 0x21,
    0xc0,

    /* U+007A "z" */
    0xf8, 0x21, 0x8, 0x41, 0xf, 0xc0,

    /* U+007B "{" */
    0x69, 0x24, 0xa2, 0x49, 0x26,

    /* U+007C "|" */
    0xff, 0xf8,

    /* U+007D "}" */
    0xc9, 0x24, 0x8a, 0x49, 0x2c,

    /* U+007E "~" */
    0x66, 0x60,

    /* U+00AA "ª" */
    0x61, 0x79, 0x50,

    /* U+00B0 "°" */
    0x24, 0x63, 0x12, 0x0,

    /* U+00BA "º" */
    0x74, 0x63, 0x12, 0x0,

    /* U+00C0 "À" */
    0x10, 0x2, 0x0, 0x0, 0x30, 0xc, 0x4, 0x81,
    0x20, 0x84, 0x21, 0x1f, 0xe4, 0xa, 0x1,

    /* U+00C1 "Á" */
    0x2, 0x1, 0x0, 0x0, 0x30, 0xc, 0x4, 0x81,
    0x20, 0x84, 0x21, 0x1f, 0xe4, 0xa, 0x1,

    /* U+00C2 "Â" */
    0x8, 0x5, 0x80, 0x0, 0x30, 0xc, 0x4, 0x81,
    0x20, 0x84, 0x21, 0x1f, 0xe4, 0xa, 0x1,

    /* U+00C3 "Ã" */
    0x18, 0x1, 0x0, 0x0, 0x30, 0xc, 0x4, 0x81,
    0x20, 0x84, 0x21, 0x1f, 0xe4, 0xa, 0x1,

    /* U+00C7 "Ç" */
    0x1e, 0x61, 0xc0, 0x80, 0x80, 0x80, 0xc0, 0x40,
    0x3f, 0x8, 0x8, 0x1c,

    /* U+00C9 "É" */
    0x4, 0x30, 0x7, 0xf8, 0x10, 0x20, 0x7e, 0x81,
    0x2, 0x7, 0xf0,

    /* U+00CA "Ê" */
    0x10, 0x50, 0x7, 0xf8, 0x10, 0x20, 0x7e, 0x81,
    0x2, 0x7, 0xf0,

    /* U+00CD "Í" */
    0x38, 0x49, 0x24, 0x92, 0x40,

    /* U+00D3 "Ó" */
    0x2, 0x1, 0x0, 0x0, 0x78, 0x61, 0xb0, 0x28,
    0x6, 0x1, 0x80, 0x70, 0x34, 0x8, 0xfc,

    /* U+00D4 "Ô" */
    0x8, 0x5, 0x0, 0x0, 0x78, 0x61, 0xb0, 0x28,
    0x6, 0x1, 0x80, 0x70, 0x34, 0x8, 0xfc,

    /* U+00D5 "Õ" */
    0x8, 0x1, 0x0, 0x0, 0x78, 0x61, 0xb0, 0x28,
    0x6, 0x1, 0x80, 0x70, 0x34, 0x8, 0xfc,

    /* U+00DA "Ú" */
    0x4, 0x8, 0x0, 0x81, 0x81, 0x81, 0x81, 0x81,
    0x81, 0x81, 0x42, 0x3c,

    /* U+00E0 "à" */
    0x20, 0x40, 0x1e, 0x4, 0x17, 0xe1, 0x85, 0xf0,

    /* U+00E1 "á" */
    0x10, 0x0, 0x1e, 0x4, 0x17, 0xe1, 0x85, 0xf0,

    /* U+00E2 "â" */
    0x30, 0xa0, 0x1e, 0x4, 0x17, 0xe1, 0x85, 0xf0,

    /* U+00E3 "ã" */
    0x78, 0x7, 0x81, 0x5, 0xf8, 0x61, 0x7c,

    /* U+00E7 "ç" */
    0x3c, 0x82, 0x4, 0x8, 0x8, 0xf, 0x8, 0x10,
    0x70,

    /* U+00E9 "é" */
    0x8, 0x20, 0x1, 0xc4, 0x50, 0x7f, 0xc0, 0x40,
    0x78,

    /* U+00EA "ê" */
    0x10, 0x50, 0x1, 0xc4, 0x50, 0x7f, 0xc0, 0x40,
    0x78,

    /* U+00ED "í" */
    0x50, 0x49, 0x24, 0x90,

    /* U+00F3 "ó" */
    0x8, 0x20, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x44,
    0x70,

    /* U+00F4 "ô" */
    0x10, 0x50, 0x1, 0xc4, 0x50, 0x60, 0xc1, 0x44,
    0x70,

    /* U+00F5 "õ" */
    0x38, 0x0, 0xe2, 0x28, 0x30, 0x60, 0xa2, 0x38,

    /* U+00FA "ú" */
    0x8, 0x20, 0x4, 0x18, 0x30, 0x60, 0xc1, 0x86,
    0xf4
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 58, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 56, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 5, .adv_w = 155, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 136, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 28, .adv_w = 183, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 147, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 50, .adv_w = 43, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 51, .adv_w = 72, .box_w = 3, .box_h = 13, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 56, .adv_w = 72, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 61, .adv_w = 84, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 65, .adv_w = 127, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 70, .adv_w = 45, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 71, .adv_w = 85, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 72, .adv_w = 45, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 72, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 82, .adv_w = 147, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 79, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 126, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 146, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 130, .adv_w = 135, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 130, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 142, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 135, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 45, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 45, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 166, .adv_w = 127, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 170, .adv_w = 127, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 173, .adv_w = 127, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 177, .adv_w = 126, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 231, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 205, .adv_w = 158, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 168, .box_w = 8, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 158, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 185, .box_w = 9, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 150, .box_w = 7, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 141, .box_w = 7, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 173, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 182, .box_w = 8, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 66, .box_w = 1, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 110, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 293, .adv_w = 157, .box_w = 8, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 131, .box_w = 7, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 214, .box_w = 10, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 182, .box_w = 8, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 188, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 188, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 366, .adv_w = 161, .box_w = 8, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 136, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 126, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 394, .adv_w = 178, .box_w = 8, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 154, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 246, .box_w = 14, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 144, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 140, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 145, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 69, .box_w = 3, .box_h = 13, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 467, .adv_w = 72, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 476, .adv_w = 69, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 481, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 486, .adv_w = 112, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 487, .adv_w = 134, .box_w = 3, .box_h = 2, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 488, .adv_w = 131, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 151, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 124, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 151, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 526, .adv_w = 73, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 153, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 543, .adv_w = 151, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 552, .adv_w = 58, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 60, .box_w = 4, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 561, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 570, .adv_w = 58, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 572, .adv_w = 238, .box_w = 13, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 584, .adv_w = 151, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 591, .adv_w = 139, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 598, .adv_w = 151, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 607, .adv_w = 151, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 616, .adv_w = 88, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 107, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 89, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 150, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 646, .adv_w = 193, .box_w = 12, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 657, .adv_w = 116, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 664, .adv_w = 118, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 673, .adv_w = 113, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 679, .adv_w = 72, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 684, .adv_w = 65, .box_w = 1, .box_h = 13, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 686, .adv_w = 72, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 691, .adv_w = 127, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 693, .adv_w = 89, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 696, .adv_w = 94, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 700, .adv_w = 92, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 704, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 719, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 734, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 749, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 764, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 776, .adv_w = 150, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 787, .adv_w = 150, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 798, .adv_w = 66, .box_w = 3, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 803, .adv_w = 188, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 818, .adv_w = 188, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 833, .adv_w = 188, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 848, .adv_w = 178, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 860, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 868, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 876, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 884, .adv_w = 131, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 891, .adv_w = 124, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 900, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 909, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 918, .adv_w = 58, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 922, .adv_w = 139, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 931, .adv_w = 139, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 940, .adv_w = 139, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 948, .adv_w = 150, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x6, 0x10, 0x16, 0x17, 0x18, 0x19, 0x1d,
    0x1f, 0x20, 0x23, 0x29, 0x2a, 0x2b, 0x30, 0x36,
    0x37, 0x38, 0x39, 0x3d, 0x3f, 0x40, 0x43, 0x49,
    0x4a, 0x4b, 0x50
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 170, .range_length = 81, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 27, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};

extern const lv_font_t montserrat_pt_14;


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t montserrat_pt_14 = {
#else
lv_font_t montserrat_pt_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif

    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &montserrat_pt_14,
#endif
    .user_data = NULL,
};



#endif /*#if MONTSERRAT_PT_14*/
