#include<allegro5/allegro.h>
#include "screen.h"
#include "stdio.h"

void screen_init(screen_t **screen, int width, int height) {
  ALLEGRO_DISPLAY *display = NULL;

  if(!al_init()) {
    fprintf(stderr, "Failed to initialize Allegro!\n");
  }

  display = al_create_display(width, height);
  if(!display) {
    fprintf(stderr, "Failed to create display!\n");
  }
  al_set_target_bitmap(al_get_backbuffer(display));
  al_clear_to_color(al_map_rgb(255, 255, 255));
  ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(display);
  *screen = display;
}


void screen_update(screen_t *screen, bitmap_t *bmp) {
  ALLEGRO_BITMAP *backbuffer = al_get_backbuffer((ALLEGRO_DISPLAY*)screen);
  
  ALLEGRO_LOCKED_REGION *locked_bitmap = al_lock_bitmap(backbuffer, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);

  al_set_target_bitmap(backbuffer);

  int x, y;
  for(y=0; y<bmp->h; y++) {
    for(x=0; x<bmp->w; x++) {
      ALLEGRO_COLOR color = al_map_rgb(
          (bmp->data[y*bmp->w + x] & 0xFF0000) >> 16, 
          (bmp->data[y*bmp->w + x] & 0x00FF00) >> 8, 
          (bmp->data[y*bmp->w + x] & 0x0000FF));
      al_put_pixel(x, y, color);
    }
  }
  
  al_unlock_bitmap(backbuffer);
  al_flip_display();
}
