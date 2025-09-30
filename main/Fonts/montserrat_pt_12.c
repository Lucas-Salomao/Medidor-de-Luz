/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --no-compress --stride 1 --align 1 --font Montserrat-Light.ttf --symbols 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáàâãéêíóôõúçÁÀÂÃÉÊÍÓÔÕÚÇ !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~°ªº --format lvgl -o montserrat_pt_12.c
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



#ifndef MONTSERRAT_PT_12
#define MONTSERRAT_PT_12 1
#endif

#if MONTSERRAT_PT_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfd,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x24, 0x24, 0x3e, 0x24, 0x24, 0xff, 0x24, 0x4,

    /* U+0024 "$" */
    0x10, 0x21, 0xf4, 0x89, 0xa, 0xf, 0x9, 0x13,
    0xf8, 0x40, 0x80,

    /* U+0025 "%" */
    0xe0, 0x49, 0x25, 0x13, 0x67, 0x48, 0xa4, 0x92,
    0xe,

    /* U+0026 "&" */
    0x30, 0x91, 0x41, 0x5, 0x11, 0xa1, 0x3d,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x6a, 0xaa, 0x90,

    /* U+0029 ")" */
    0xa9, 0x55, 0xa0,

    /* U+002A "*" */
    0x5f, 0xa0,

    /* U+002B "+" */
    0x21, 0x3e, 0x42, 0x0,

    /* U+002C "," */
    0xc0,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x11, 0x22, 0x24, 0x44, 0x88, 0x80,

    /* U+0030 "0" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x1c,

    /* U+0031 "1" */
    0xe4, 0x92, 0x49,

    /* U+0032 "2" */
    0x78, 0x10, 0x42, 0x8, 0x42, 0x1f,

    /* U+0033 "3" */
    0xf8, 0x21, 0xc, 0xc, 0x10, 0x7e,

    /* U+0034 "4" */
    0x8, 0x10, 0x20, 0x24, 0x44, 0xff, 0x4, 0x4,

    /* U+0035 "5" */
    0x7a, 0x8, 0x1c, 0xc, 0x10, 0x7e,

    /* U+0036 "6" */
    0x3c, 0x82, 0x5, 0xcc, 0x50, 0x60, 0xbe,

    /* U+0037 "7" */
    0xfe, 0x10, 0x82, 0x10, 0x42, 0x8,

    /* U+0038 "8" */
    0x79, 0xa, 0x13, 0xc8, 0x50, 0x60, 0xbe,

    /* U+0039 "9" */
    0x79, 0xa, 0xc, 0x37, 0xa0, 0x41, 0x3c,

    /* U+003A ":" */
    0x84,

    /* U+003B ";" */
    0x86,

    /* U+003C "<" */
    0x1b, 0x30, 0x70,

    /* U+003D "=" */
    0xf8, 0x1, 0xf0,

    /* U+003E ">" */
    0xc1, 0x87, 0xc0,

    /* U+003F "?" */
    0x78, 0x10, 0x42, 0x10, 0x40, 0x4,

    /* U+0040 "@" */
    0x1f, 0x86, 0x4, 0x8e, 0xab, 0x19, 0xa0, 0x9a,
    0x9, 0xa0, 0x99, 0xbe, 0x44, 0x3, 0xf0,

    /* U+0041 "A" */
    0x8, 0x18, 0x24, 0x24, 0x42, 0x7e, 0x81, 0x81,

    /* U+0042 "B" */
    0xfd, 0x6, 0xf, 0xe8, 0x70, 0x60, 0xfe,

    /* U+0043 "C" */
    0x3e, 0x40, 0x80, 0x80, 0x80, 0x80, 0x40, 0x3e,

    /* U+0044 "D" */
    0xfc, 0x82, 0x81, 0x81, 0x81, 0x81, 0x82, 0xfc,

    /* U+0045 "E" */
    0xfe, 0x8, 0x3e, 0x82, 0x8, 0x3f,

    /* U+0046 "F" */
    0xfe, 0x8, 0x20, 0xfa, 0x8, 0x20,

    /* U+0047 "G" */
    0x3e, 0x40, 0x80, 0x80, 0x81, 0x81, 0x41, 0x3e,

    /* U+0048 "H" */
    0x83, 0x6, 0xf, 0xf8, 0x30, 0x60, 0xc1,

    /* U+0049 "I" */
    0xff,

    /* U+004A "J" */
    0x78, 0x42, 0x10, 0x84, 0x2e,

    /* U+004B "K" */
    0x85, 0x12, 0x45, 0xd, 0x11, 0x21, 0x41,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x3f,

    /* U+004D "M" */
    0x80, 0xe0, 0xf0, 0xb4, 0x5a, 0x4c, 0xa6, 0x23,
    0x1,

    /* U+004E "N" */
    0x83, 0x86, 0x8d, 0x19, 0x31, 0x61, 0xc1,

    /* U+004F "O" */
    0x3e, 0x20, 0xa0, 0x30, 0x18, 0xc, 0x5, 0x4,
    0x7c,

    /* U+0050 "P" */
    0xf9, 0xa, 0xc, 0x18, 0x5f, 0x20, 0x40,

    /* U+0051 "Q" */
    0x3e, 0x20, 0xa0, 0x30, 0x18, 0xc, 0x5, 0x4,
    0x7c, 0x4, 0x1, 0xc0,

    /* U+0052 "R" */
    0xf9, 0xa, 0xc, 0x18, 0x5f, 0x21, 0x43,

    /* U+0053 "S" */
    0x7a, 0x8, 0x10, 0x38, 0x10, 0x7e,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8,

    /* U+0055 "U" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x61, 0x3c,

    /* U+0056 "V" */
    0x81, 0x82, 0x42, 0x42, 0x24, 0x24, 0x18, 0x8,

    /* U+0057 "W" */
    0x82, 0xa, 0x30, 0x91, 0x44, 0x8a, 0x42, 0x8a,
    0x14, 0x50, 0xa3, 0x2, 0x8,

    /* U+0058 "X" */
    0x42, 0x88, 0xa0, 0xc1, 0x85, 0x11, 0x41,

    /* U+0059 "Y" */
    0x83, 0x9, 0x11, 0x43, 0x2, 0x4, 0x8,

    /* U+005A "Z" */
    0xfc, 0x8, 0x20, 0x82, 0x8, 0x10, 0x7f,

    /* U+005B "[" */
    0xea, 0xaa, 0xb0,

    /* U+005C "\\" */
    0x88, 0x88, 0x44, 0x22, 0x21, 0x10,

    /* U+005D "]" */
    0xd5, 0x55, 0x70,

    /* U+005E "^" */
    0x23, 0x15, 0x28, 0x80,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0x90,

    /* U+0061 "a" */
    0x78, 0x13, 0xe1, 0x85, 0xf0,

    /* U+0062 "b" */
    0x81, 0x2, 0xe6, 0x28, 0x30, 0x61, 0x7c,

    /* U+0063 "c" */
    0x3b, 0x8, 0x20, 0x81, 0xe0,

    /* U+0064 "d" */
    0x2, 0x4, 0xee, 0x38, 0x30, 0x60, 0xbf,

    /* U+0065 "e" */
    0x7a, 0x1f, 0xe0, 0x80, 0xe0,

    /* U+0066 "f" */
    0x34, 0x64, 0x44, 0x44,

    /* U+0067 "g" */
    0x3b, 0x8e, 0xc, 0x18, 0x2f, 0xc0, 0xbe,

    /* U+0068 "h" */
    0x82, 0xb, 0xb1, 0x86, 0x18, 0x61,

    /* U+0069 "i" */
    0xbf,

    /* U+006A "j" */
    0x20, 0x92, 0x49, 0x38,

    /* U+006B "k" */
    0x82, 0x8, 0xa4, 0xa3, 0x48, 0xa2,

    /* U+006C "l" */
    0xff,

    /* U+006D "m" */
    0xbb, 0xd8, 0x86, 0x10, 0xc2, 0x18, 0x43, 0x8,
    0x40,

    /* U+006E "n" */
    0xbb, 0x18, 0x61, 0x86, 0x10,

    /* U+006F "o" */
    0x39, 0x8a, 0xc, 0x18, 0x4f, 0x0,

    /* U+0070 "p" */
    0xb9, 0x8a, 0xc, 0x18, 0x5f, 0x20, 0x40,

    /* U+0071 "q" */
    0x3b, 0x8e, 0xc, 0x18, 0x2f, 0xc0, 0x81,

    /* U+0072 "r" */
    0xf2, 0x49, 0x0,

    /* U+0073 "s" */
    0x74, 0x10, 0x60, 0xf8,

    /* U+0074 "t" */
    0x44, 0x64, 0x44, 0x43,

    /* U+0075 "u" */
    0x86, 0x18, 0x61, 0x85, 0xf0,

    /* U+0076 "v" */
    0x86, 0x14, 0x92, 0x30, 0x40,

    /* U+0077 "w" */
    0x84, 0x63, 0x15, 0x49, 0x4a, 0x53, 0x8, 0x40,

    /* U+0078 "x" */
    0x49, 0x23, 0xc, 0x4a, 0x10,

    /* U+0079 "y" */
    0x86, 0x14, 0x92, 0x30, 0x42, 0x30,

    /* U+007A "z" */
    0x78, 0x88, 0x84, 0x78,

    /* U+007B "{" */
    0x69, 0x28, 0x92, 0x4c,

    /* U+007C "|" */
    0xff, 0xc0,

    /* U+007D "}" */
    0xc9, 0x22, 0x92, 0x58,

    /* U+007E "~" */
    0x45, 0xc0,

    /* U+00AA "ª" */
    0xe7, 0x95,

    /* U+00B0 "°" */
    0x69, 0x96,

    /* U+00BA "º" */
    0x74, 0x62, 0xe0,

    /* U+00C0 "À" */
    0x10, 0x8, 0x8, 0x18, 0x24, 0x24, 0x42, 0x7e,
    0x81, 0x81,

    /* U+00C1 "Á" */
    0x8, 0x0, 0x8, 0x18, 0x24, 0x24, 0x42, 0x7e,
    0x81, 0x81,

    /* U+00C2 "Â" */
    0x18, 0x24, 0x8, 0x18, 0x24, 0x24, 0x42, 0x7e,
    0x81, 0x81,

    /* U+00C3 "Ã" */
    0x10, 0x2c, 0x8, 0x18, 0x24, 0x24, 0x42, 0x7e,
    0x81, 0x81,

    /* U+00C7 "Ç" */
    0x3e, 0x40, 0x80, 0x80, 0x80, 0x80, 0x40, 0x3e,
    0x8, 0xc,

    /* U+00C9 "É" */
    0x10, 0x8f, 0xe0, 0x83, 0xe8, 0x20, 0x83, 0xf0,

    /* U+00CA "Ê" */
    0x31, 0x2f, 0xe0, 0x83, 0xe8, 0x20, 0x83, 0xf0,

    /* U+00CD "Í" */
    0x6a, 0xaa, 0xa0,

    /* U+00D3 "Ó" */
    0x4, 0x4, 0xf, 0x88, 0x28, 0xc, 0x6, 0x3,
    0x1, 0x41, 0x1f, 0x0,

    /* U+00D4 "Ô" */
    0x18, 0x2, 0xf, 0x88, 0x28, 0xc, 0x6, 0x3,
    0x1, 0x41, 0x1f, 0x0,

    /* U+00D5 "Õ" */
    0x10, 0x6, 0xf, 0x88, 0x28, 0xc, 0x6, 0x3,
    0x1, 0x41, 0x1f, 0x0,

    /* U+00DA "Ú" */
    0x8, 0x22, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x84,
    0xf0,

    /* U+00E0 "à" */
    0x20, 0x7, 0x81, 0x3e, 0x18, 0x5f,

    /* U+00E1 "á" */
    0x10, 0x7, 0x81, 0x3e, 0x18, 0x5f,

    /* U+00E2 "â" */
    0x30, 0x7, 0x81, 0x3e, 0x18, 0x5f,

    /* U+00E3 "ã" */
    0x78, 0x7, 0x81, 0x3e, 0x18, 0x5f,

    /* U+00E7 "ç" */
    0x3b, 0x8, 0x20, 0x81, 0xe1, 0x4,

    /* U+00E9 "é" */
    0x10, 0x7, 0xa1, 0xfe, 0x8, 0xe,

    /* U+00EA "ê" */
    0x30, 0x7, 0xa1, 0xfe, 0x8, 0xe,

    /* U+00ED "í" */
    0x4a, 0xaa,

    /* U+00F3 "ó" */
    0x8, 0x0, 0xe6, 0x28, 0x30, 0x61, 0x3c,

    /* U+00F4 "ô" */
    0x38, 0x0, 0xe6, 0x28, 0x30, 0x61, 0x3c,

    /* U+00F5 "õ" */
    0x18, 0x0, 0xe6, 0x28, 0x30, 0x61, 0x3c,

    /* U+00FA "ú" */
    0x10, 0x8, 0x61, 0x86, 0x18, 0x5f
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 49, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 48, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 69, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 4, .adv_w = 132, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 117, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 23, .adv_w = 157, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 126, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 37, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 40, .adv_w = 62, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 43, .adv_w = 62, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 46, .adv_w = 72, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 48, .adv_w = 109, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 52, .adv_w = 38, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 53, .adv_w = 73, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 54, .adv_w = 38, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 61, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 61, .adv_w = 126, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 68, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 71, .adv_w = 108, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 77, .adv_w = 107, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 126, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 107, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 116, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 121, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 116, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 38, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 38, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 126, .adv_w = 109, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 129, .adv_w = 109, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 132, .adv_w = 109, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 135, .adv_w = 108, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 198, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 156, .adv_w = 135, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 144, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 136, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 159, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 121, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 148, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 57, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 135, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 184, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 161, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 137, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 265, .adv_w = 161, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 277, .adv_w = 138, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 117, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 108, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 152, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 132, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 211, .box_w = 13, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 325, .adv_w = 123, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 120, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 346, .adv_w = 59, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 349, .adv_w = 61, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 355, .adv_w = 59, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 358, .adv_w = 109, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 362, .adv_w = 96, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 363, .adv_w = 115, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 364, .adv_w = 112, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 369, .adv_w = 130, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 107, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 130, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 63, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 404, .adv_w = 129, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 410, .adv_w = 50, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 51, .box_w = 3, .box_h = 10, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 415, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 50, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 204, .box_w = 11, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 129, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 119, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 130, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 449, .adv_w = 130, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 456, .adv_w = 76, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 92, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 76, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 101, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 477, .adv_w = 166, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 490, .adv_w = 101, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 496, .adv_w = 97, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 61, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 504, .adv_w = 56, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 506, .adv_w = 61, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 510, .adv_w = 109, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 512, .adv_w = 76, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 514, .adv_w = 81, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 516, .adv_w = 79, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 519, .adv_w = 135, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 529, .adv_w = 135, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 539, .adv_w = 135, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 549, .adv_w = 135, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 559, .adv_w = 136, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 569, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 577, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 57, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 588, .adv_w = 161, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 600, .adv_w = 161, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 161, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 152, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 633, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 645, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 657, .adv_w = 107, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 663, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 669, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 675, .adv_w = 50, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 119, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 119, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 691, .adv_w = 119, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0}
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

extern const lv_font_t montserrat_pt_12;


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t montserrat_pt_12 = {
#else
lv_font_t montserrat_pt_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 12,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif

    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &montserrat_pt_12,
#endif
    .user_data = NULL,
};



#endif /*#if MONTSERRAT_PT_12*/
