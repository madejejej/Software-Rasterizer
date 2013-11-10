/**
 * Funkcje do obslugi bitmap
 */
#ifndef __BITMAP_H__
#define __BITMAP_H__
#include"types.h"

/**
 * Ustawia kolor pixela
 */
void put_pixel(bitmap_t *bmp, int x, int y, color_t color);
#endif
