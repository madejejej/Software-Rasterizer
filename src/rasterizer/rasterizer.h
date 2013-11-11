/**
 * Rasteryzacja trojkatow
 */
#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__
#include"../types.h"
#include"../bitmap.h"

/**
 * Funkcja sluzaca do rasteryzacji
 * @param bmp - bitmapa na ktorej zrasteryzowane zostana trojkaty
 * @param triangles - tablica trojkatow
 * @param n - liczba trojkatow
 */
void rasterize(bitmap_t *bmp, triangle2d_t *triangles, int n);

/**
 * Funkcja czyszczaca zaalokowana pamiec
 * aby zapobiec wyciekom pamieci musi byc wywolana przed zakonczeniem programu.
 */
void rasterizer_free_memory();
#endif
