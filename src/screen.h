#ifndef __SCREEN_H__
#define __SCREEN_H__
#include<allegro5/allegro.h>
#include"types.h"

typedef ALLEGRO_DISPLAY screen_t;

void screen_init(screen_t **screen, int width, int height);
void screen_update(screen_t *screen, bitmap_t *bmp);
#endif
