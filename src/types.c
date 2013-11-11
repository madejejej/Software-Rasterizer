#include"types.h"

point2d_t point2d_init(float x, float y, unsigned int depth, color_t color) {
  point2d_t p;
  p.x = x; p.y = y;
  p.depth = depth;
  p.color = color;
  return p;
}

triangle2d_t triangle2d_init(point2d_t x, point2d_t y, point2d_t z) {
  triangle2d_t tri;
  tri.v1 = x;
  tri.v2 = y;
  tri.v3 = z;
  return tri;
}
