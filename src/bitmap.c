#include"bitmap.h"

void put_pixel(bitmap_t *bmp, int x, int y, color_t color) {
  if(x >= 0 && x < bmp->w && y >= 0 && y < bmp->h) {
    bmp->data[y*bmp->w + x] = color;
  }
}
