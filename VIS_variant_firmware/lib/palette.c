#include "palette.h"
#include "lcd.h"
#include "settings.h"
#include <pico/stdlib.h>

typedef struct {
    const char *name;
    uint32_t colors[4];
} pal_t;

// Intro/splash screen palette 
static const uint8_t splash_palette[12][3] = {
    {255, 255, 255}, {0, 0, 0}, {62, 153, 88}, {123, 224, 207},
    {237, 240, 239}, {218, 222, 220}, {170, 217, 192}, {148, 160, 151},
    {246, 247, 246}, {198, 198, 198}, {94, 94, 94}, {40, 40, 40}
};

static const pal_t palettes[] = {
    {"Default",        {0xB0CB65, 0x607623, 0x415115, 0x1A2108}},
    {"Monochrome",     {0xD2D2D2, 0xAAAAAA, 0x555555, 0x000000}},
    {"DMG Classic",    {0x9BBC0F, 0x8BAC0F, 0x306230, 0x0F380F}},
    {"DMG Tetris",     {0xFFFFFF, 0xFFFF00, 0xFF0000, 0x000000}},
    {"SNES",           {0xF7E7C6, 0xD68E49, 0xA63725, 0x331E50}},
    {"CGB Default",    {0xFFFFB5, 0x7BFF31, 0x00AD52, 0x000000}},
    {"CGB Blue",       {0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000}},
    {"CGB Dark Blue",  {0xFFFFFF, 0x8C8CDE, 0x52528C, 0x000000}},
    {"CGB Gray",       {0xFFFFFF, 0xA5A5A5, 0x525252, 0x000000}},
    {"CGB Pastel",     {0xFFFFA5, 0xFF9494, 0x9494FF, 0x000000}},
    {"CGB Orange",     {0xFFFFFF, 0xFFFF00, 0xFF0000, 0x000000}},
    {"CGB Yellow",     {0xFFFFFF, 0xFFFF00, 0x7B4A00, 0x000000}},
    {"CGB Green",      {0xFFFFFF, 0x52FF00, 0xFF4200, 0x000000}},
    {"CGB Dark Green", {0xFFFFFF, 0x7BFF31, 0x0063C5, 0x000000}},
    {"CGB Inverted",   {0x000000, 0x008484, 0xFFDE00, 0xFFFFFF}},
};

static uint8_t current_palette_index = 0;

void palette_init(void) {
    current_palette_index = settings_get_palette();
    palette_apply(current_palette_index);
}

void palette_apply(uint8_t index)
{
    if (index >= sizeof(palettes)/sizeof(palettes[0])) return;
    
    current_palette_index = index;
    
    for (int i=0;i<4;i++)
    {
        uint32_t c = palettes[index].colors[i];
        
        uint8_t r = (c >> 16) & 0xFF;
        uint8_t g = (c >> 8) & 0xFF;
        uint8_t b = c & 0xFF;
        
        lcd_set_palette(i, RGB(r, g, b));
    }
    
}

void palette_apply_splash(void)
{
    for(int i = 0; i < 12; i++)
    {
        uint8_t r = splash_palette[i][0];
        uint8_t g = splash_palette[i][1];
        uint8_t b = splash_palette[i][2];

        lcd_set_palette(i, RGB(r, g, b));
    }
}

uint8_t palette_count(void) {
    return sizeof(palettes) / sizeof(palettes[0]);
}

const char* palette_name(uint8_t index) {
    if (index >= palette_count()) return "Unknown";
    return palettes[index].name;
}

uint8_t palette_current(void) {
    return current_palette_index;
}

void palette_apply_no_save(uint8_t index) {
    palette_apply(index);
    settings_set_palette(index);
}