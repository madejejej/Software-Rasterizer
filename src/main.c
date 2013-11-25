#include"screen.h"
#include"types.h"
#include"rasterizer/rasterizer.h"
#include"scene/scene.h"
#include"scene/scene_file.h"

#include<stdio.h>

#define WIDTH 1000 
#define HEIGHT 1000 

ALLEGRO_EVENT_QUEUE *event_queue;
screen_t *display;
scene_t *scene;
bitmap_t bmp;

void setup();
void render();
void cleanup();

int main(int argc, char **arv) {
  setup();

  while(true) {
    render();
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      break;
    }
  }

  cleanup();
  return 0;
}

void setup() {
  screen_init(&display, WIDTH, HEIGHT);

  bmp.w = WIDTH;
  bmp.h = HEIGHT;
  bmp.data = (color_t*)malloc(bmp.w*bmp.h*sizeof(int));
  int i;
  for(i=0; i<bmp.w*bmp.h; i++) {
    bmp.data[i] = 0x000000;
  }

  FILE *sceneFile = fopen("scenes/scene1.scene", "r");
  if(!sceneFile) {
    fprintf(stderr, "Cant open scene file!\n");
    exit(-1);
  }
  scene = read_scene_from_file(sceneFile);
  fclose(sceneFile);

  event_queue = al_create_event_queue();
  al_register_event_source(event_queue, al_get_display_event_source(display));
}

void render() {
  scene_draw(scene, &bmp);
  screen_update(display, &bmp);
}


void cleanup() {
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  rasterizer_free_memory();
  free(bmp.data);
}

void render_sample_triangle() {
  screen_init(&display, WIDTH, HEIGHT);
  bmp.w = WIDTH;
  bmp.h = HEIGHT;
  bmp.data = (color_t*)malloc(bmp.w*bmp.h*sizeof(int));
  int i;
  for(i=0; i<bmp.w*bmp.h; i++) {
    bmp.data[i] = 0xFF0000;
  }
  for(i=0; i<5; i++)
    screen_update(display, &bmp);

  triangle2d_t tri = triangle2d_init( 
      point2d_init(100, 100, 10, 0xFF0000), 
      point2d_init(500, 100, 100, 0x00FF00), 
      point2d_init(300, 500, 5, 0x0000FF) );

  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  event_queue = al_create_event_queue();
  al_register_event_source(event_queue, al_get_display_event_source(display));

  while(true) {
    rasterize(&bmp, &tri, 1);
    screen_update(display, &bmp);
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      break;
    }
  }
}
