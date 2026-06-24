#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include <stdint.h>

void brightness_init(void);

void brightness_up(void);

void brightness_down(void);

void brightness_apply(void);

uint8_t brightness_get_level(void);

#endif // BRIGHTNESS_H