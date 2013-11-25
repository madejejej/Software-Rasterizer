#include"rasterizer.h"
#include"../bitmap.h"
#include<limits.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>

#define f01(x,y) ((y0-y1)*x + (x1-x0)*y + x0*y1 - x1*y0)
#define f12(x,y) ((y1-y2)*x + (x2-x1)*y + x1*y2 - x2*y1)
#define f20(x,y) ((y2-y0)*x + (x0-x2)*y + x2*y0 - x0*y2)
#define RED(x) ((x & 0xFF0000) >> 16)
#define GREEN(x) ((x & 0x00FF00) >> 8)
#define BLUE(x) ((x & 0x0000FF))
#define CLAMP(val, x, y) (val < x ? x : (val > y ? y : val))

color_t interp_colors(color_t c1, color_t c2, color_t c3, float a, float b, float c); 

unsigned int interp_uint(unsigned int x, unsigned int y, unsigned int z, float a, float b, float c); 
 
unsigned int *depth_buffer = NULL;
int depth_buffer_size;

void init_depth_buffer(int width, int height) {
  depth_buffer_size = width*height;
  depth_buffer = (unsigned int*)malloc(depth_buffer_size*sizeof(unsigned int));
}

void clear_depth_buffer() {
  int i;
  for(i=0;i<depth_buffer_size; i++) {
    depth_buffer[i] = INT_MAX;
  }
}

void destroy_depth_buffer() {
  free(depth_buffer);
  depth_buffer = NULL;
}

void rasterize(bitmap_t *bmp, triangle2d_t *triangles, int n) {
  if(!depth_buffer) {
    init_depth_buffer(bmp->w, bmp->h);
  }
  clear_depth_buffer();
  int i;
  fprintf(stderr, "rasterization stage started...\n");
  fprintf(stderr, "%d triangles\n", n);
  for(i=0; i<n; i++) {
    triangle2d_t tri = triangles[i];
    fprintf(stderr, "Triangle %d with vertices: (%f, %f), (%f, %f), (%f, %f)\n", (i+1), tri.v1.x, tri.v1.y, tri.v2.x, tri.v2.y, tri.v3.x, tri.v3.y);

    float x0 = tri.v1.x; float y0 = tri.v1.y;
    float x1 = tri.v2.x; float y1 = tri.v2.y;
    float x2 = tri.v3.x; float y2 = tri.v3.x;
    int xmin = floor(fmin(x0, fmin(x1,x2)));
    int xmax = ceil(fmax(x0, fmax(x1,x2)));
    int ymin = floor(fmin(y0, fmin(y1,y2)));
    int ymax = ceil(fmax(y0, fmax(y1,y2)));
    float f_alpha = f12(x0, y0);
    float f_beta = f20(x1,y1);
    float f_gamma = f01(x2,y2);

    int x, y;
    for(y=ymin; y<=ymax; y++) {
      for(x=xmin; x<=xmax; x++) {
        float alpha = f12(x,y)/f_alpha;
        float beta = f20(x,y)/f_beta;
        float gamma = f01(x,y)/f_gamma;

        if(alpha > 0 && beta > 0 && gamma > 0) {
          unsigned int depth_value = interp_uint(tri.v1.depth,
              tri.v2.depth, tri.v3.depth, alpha, beta, gamma);
          if(depth_value > depth_buffer[y*bmp->w + x]) {
            continue;
          }
          depth_buffer[y*bmp->w + x] = depth_value;
          color_t col = interp_colors(tri.v1.color, tri.v2.color, tri.v3.color, alpha, beta, gamma);
          put_pixel(bmp, x, y, col);
        }
      }
    }
  }
}


color_t interp_colors(color_t c1, color_t c2, color_t c3, float a, float b, float c) {
  int red = CLAMP(a*RED(c1) + b*RED(c2) + c*RED(c3), 0, 255);
  int green = CLAMP(a*GREEN(c1) +b*GREEN(c2) + c*GREEN(c3), 0, 255);
  int blue = CLAMP(a*BLUE(c1) + b*BLUE(c2) + c*BLUE(c3), 0, 255);
  color_t interp = (red << 16) + (green << 8) + blue;
  return interp;

}

unsigned int interp_uint(unsigned int x, unsigned int y, unsigned int z, float a, float b, float c) {
  return a*x + b*y + c*z;
}
  
void rasterizer_free_memory() {
  destroy_depth_buffer();
}

