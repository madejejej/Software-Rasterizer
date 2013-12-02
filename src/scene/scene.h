#ifndef __SCENE_H__
#define __SCENE_H__
#include "../matrix/matrix.h"
#include "../types.h"
#include "camera.h"


typedef struct {
  triangle_t *tris;
  int n;
  MAT *transform;
} mesh_t;

typedef struct {
  mesh_t *meshes;
  int n;
  camera_t *camera;
  MAT *M_viewport;
  MAT *M_proj;
  int total_tris;
  float near;
  float far;
} scene_t;


void scene_draw(scene_t *scene, bitmap_t *bmp);

#endif
