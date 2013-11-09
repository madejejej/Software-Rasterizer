#include"screen.h"
#include"types.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char **arv) {
  screen_t *display = NULL;

  screen_init(&display, WIDTH, HEIGHT);
  bitmap_t bmp;
  bmp.w = WIDTH;
  bmp.h = HEIGHT;
  bmp.data = (int*)malloc(bmp.w*bmp.h*sizeof(int));
  for(int i=0; i<bmp.w*bmp.h; i++) {
    bmp.data[i] = 0xFF0000;
  }
  for(int i=0; i<5; i++)
    screen_update(display, &bmp);
  fprintf(stderr, "bmp.data[0] = (%d,%d,%d)\n",
(bmp.data[0] & 0xFF0000) >> 16, (bmp.data[0] & 0x00FF00) >> 8, (bmp.data[0] & 0x0000FF));
  al_rest(3.0);
  al_destroy_display(display);
  free(bmp.data);
  return 0;
}
