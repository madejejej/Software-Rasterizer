/**
 * Minimalny wrapper na obsluge ekranu.
 */
#ifndef __SCREEN_H__
#define __SCREEN_H__
#include<allegro5/allegro.h>
#include"types.h"

typedef ALLEGRO_DISPLAY screen_t;

/** 
 * Inicjalizacja ekranu
 * @param width - szerokosc ekranu
 * @param height - wysokosc ekranu
 */
void screen_init(screen_t **screen, int width, int height);

/**
 * Rysowanie bitmapy na ekranie
 * Bitmapa zawsze bedzie rysowana zaczynajac od lewego gornego rogu ekranu
 */
void screen_update(screen_t *screen, bitmap_t *bmp);
#endif
