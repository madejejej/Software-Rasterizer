#include "scene_file.h"
#include "../types.h"
#include "../matrix/matrix_stack.h"
#include "../transformations/transformations.h"
#include "../transformations/viewTransformations.h"
#include "../vec.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_TRI_PER_MESH 16

scene_t* read_scene_from_file(FILE *file) {
  fprintf(stderr, "Reading scene file...\n");
  initMatrixStack();
  scene_t *scene = (scene_t*)malloc(sizeof(scene_t));
  scene->total_tris = 0;
  scene->n = 0;
  scene->M_proj = getPerspectiveProjection(-9, 4, -4, 3, -3, 10000);
  scene->near = -9;
  scene->far = 10000;
  scene->M_viewport = NULL;
  scene->meshes = (mesh_t*)malloc(1024*sizeof(mesh_t));
  scene->meshes[0].tris = (triangle_t*)malloc(MAX_TRI_PER_MESH*sizeof(triangle_t));
  char cmd[1024];
  vec4_t *vertices;  
  int maxVerts;
  int currentVerts = 0;
  fcolor_t currentColor;
  currentColor.r = 0.0f;
  currentColor.g = 0.0f;
  currentColor.b = 0.0f;
  fcolor_t vertColor;
  vertColor.r = 0.0f;
  vertColor.g = 0.0f;
  vertColor.b = 0.0f;
  float width, height;
  triangle_t *tris = (triangle_t*)malloc(1024*sizeof(triangle_t));
  int currentTri = 0;
  mesh_t *currentMesh = &scene->meshes[0];
  currentMesh->transform = topMatrix();
  while(fscanf(file, "%s", cmd)) {
    if(feof(file)) {
      break;
    }
    fprintf(stderr, "Read command: %s\n", cmd);
    if(strcmp(cmd, "maxverts") == 0) {
      fscanf(file, "%d", &maxVerts);
      vertices = (vec4_t*)malloc(maxVerts*sizeof(vec4_t));
    } else if(strcmp(cmd, "size") == 0) {
      fscanf(file, "%f %f", &width, &height);
      fprintf(stderr, "Scene size: %f %f\n", width, height);
      scene->M_viewport = getViewportTransformation(width, height);
    } else if(strcmp(cmd, "vertex") == 0) {
      float x,y,z;
      fscanf(file, "%f %f %f", &x, &y, &z);
      vertices[currentVerts].x = x; 
      vertices[currentVerts].y = y; 
      vertices[currentVerts].z = z; 
      vertices[currentVerts].t = 1; 
      vertices[currentVerts].color = vertColor;
      currentVerts++;
    } else if(strcmp(cmd, "vertColor") == 0) {
      float r,g,b;
      fscanf(file, "%f %f %f", &r, &g, &b);
      vertColor.r = r;
      vertColor.g = g;
      vertColor.b = b;
    } else if(strcmp(cmd, "tri") == 0) {
      int v1,v2,v3;
      fscanf(file, "%d %d %d", &v1, &v2, &v3);
      fprintf(stderr, "Read %d triangle - points %d %d %d\n",
                currentTri, v1, v2, v3);
      fprintf(stderr, "Current mesh already has %d triangles\n", currentMesh->n);
      tris[currentTri].verts[0] = vertices[v1];
      tris[currentTri].verts[1] = vertices[v2];
      tris[currentTri].verts[2] = vertices[v3];
      scene->total_tris++;
      currentMesh->tris[currentMesh->n++] = tris[currentTri];
      currentTri++;
    } else if(cmd[0]=='#') {
      fgets(cmd, 250, file); // comment - ignore whole line
    } else if(strcmp(cmd, "pushTransform") == 0) {
      pushMatrix(m_copy(topMatrix()));
      if(currentMesh->n > 0) {
        scene->n++;
        currentMesh = &scene->meshes[scene->n];
        currentMesh->tris = (triangle_t*)malloc(MAX_TRI_PER_MESH*sizeof(triangle_t));
      }
      currentMesh->transform = topMatrix();
    } else if(strcmp(cmd, "popTransform") == 0) {
      popMatrix();
      if(currentMesh->n > 0) {
        scene->n++;
        currentMesh = &scene->meshes[scene->n];
        currentMesh->tris = (triangle_t*)malloc(MAX_TRI_PER_MESH*sizeof(triangle_t));
      }
      currentMesh->transform = topMatrix();
    } else if(strcmp(cmd, "scale") == 0) {
      float sx, sy, sz;
      fscanf(file, "%f %f %f", &sx, &sy, &sz);
      MAT *top = topMatrix();
      scale(top, sx, sy, sz);
    } else if(strcmp(cmd, "translate") == 0) {
      float dx,dy,dz;
      fscanf(file, "%f %f %f", &dx, &dy, &dz);
      MAT *top = topMatrix();
      translate(top, dx, dy, dz);
    } else if(strcmp(cmd, "rotate") == 0) {
      vec3_t axis;
      float degrees;
      fscanf(file, "%f %f %f %f", &axis.x, &axis.y, &axis.z, &degrees); 
      MAT *top = topMatrix();
      rotate(top, degrees, axis); 
    } else if(strcmp(cmd, "camera") == 0) {
      vec3_t eye, center, up;
      float fovy;
      fscanf(file, "%f %f %f %f %f %f %f %f %f %f", 
          &eye.x, &eye.y, &eye.z,
          &center.x, &center.y, &center.z,
          &up.x, &up.y, &up.z, &fovy);
      up = v3_up(eye, v3_sub(eye, center));
      scene->M_cam = lookAt( eye, center, up ); 
      // TODO
    } else if(strcmp(cmd, "ambient") == 0) {
      // TODO
    }
  } 
  return scene;
}



