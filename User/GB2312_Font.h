#ifndef GB2312_Font
#define GB2312_Font

#include <stm32f1xx.h>
#include <stm32f1xx_hal.h>

extern const char V_font_ascii_table_conslons_16x8[];
extern const char V_font_ascii_table_conslons_24x16[];
extern const char V_font_ascii_table_conslons_32x24[];

typedef struct
{
    const char *font_table;
    const uint8_t width;
    const uint8_t height;
} Type_Font_ASCII;

extern Type_Font_ASCII V_font_ascii_handle_conslons_16x8;
extern Type_Font_ASCII V_font_ascii_handle_conslons_24x16;
extern Type_Font_ASCII V_font_ascii_handle_conslons_32x24;

#endif
