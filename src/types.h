#ifndef __TYPES_H__
#define __TYPES_H__

typedef unsigned int color_t;

typedef struct {
  float x,y,z,t;
  color_t color;
} vec4_t;

typedef struct {
  vec4_t v1,v2,v3;
} triangle_t;

/**
 * Bitmapa
 * @param w szerokosc bitmapy
 * @param h wysokosc bitmapy
 * @param data tablica rozmiaru w*h trzymajaca pixele rzedami od lewego gornego rogu
 */
typedef struct {
  int w;
  int h;
  color_t *data;
} bitmap_t;

/**
 * Punkt we wspolrzednych ekranu
 */
typedef struct {
  float x,y;
  color_t color;
} point2d_t;

/**
 * Trojkat we wspolrzednych ekranu
 */
typedef struct {
  point2d_t v1,v2,v3;
} triangle2d_t;


/**
 * Tworzy nowy point2d_t
 */
point2d_t point2d_init(float x, float y, color_t color);

/**
 * Tworzy nowy triangle2d_t z trzech punktow
 */
triangle2d_t triangle2d_init(point2d_t x, point2d_t y, point2d_t z);


#endif
