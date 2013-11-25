#include "scene_file.h"
#include "../types.h"
#include "../matrix/matrix_stack.h"
#include "../transformations/transformations.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

scene_t* read_scene_from_file(FILE *file) {
  scene_t *scene = (scene_t*)malloc(sizeof(scene_t));
  scene->total_tris = 0;
  scene->n = 0;
  scene->meshes = (mesh_t*)malloc(1024*sizeof(mesh_t));
  char cmd[256];
  vec4_t *vertices;  
  int maxVerts;
  int currentVerts = 0;
  fcolor_t currentColor;
  int width, height;
  triangle_t *tris = (triangle_t*)malloc(1024*sizeof(triangle_t));
  int currentTri = 0;
  mesh_t *currentMesh = &scene->meshes[0];
  fscanf(file, "%s", cmd);
  if(strcmp(cmd, "maxverts") == 0) {
    fscanf(file, "%d", &maxVerts);
    vertices = (vec4_t*)malloc(maxVerts*sizeof(vec4_t));
  } else if(strcmp(cmd, "size") == 0) {
    fscanf(file, "%d %d", &width, &height);
  } else if(strcmp(cmd, "vertex") == 0) {
    float x,y,z;
    fscanf(file, "%f %f %f", &x, &y, &z);
    vertices[currentVerts].x = x; 
    vertices[currentVerts].y = y; 
    vertices[currentVerts].z = z; 
    vertices[currentVerts].t = 1; 
    vertices[currentVerts].color = currentColor;
    currentVerts++;
  } else if(strcmp(cmd, "ambient") == 0) {
    float r,g,b;
    fscanf(file, "%f %f %f", &r, &g, &b);
    currentColor.r = r;
    currentColor.g = g;
    currentColor.b = b;
  } else if(strcmp(cmd, "tri") == 0) {
    int v1,v2,v3;
    fscanf(file, "%d %d %d", &v1, &v2, &v3);
    tris[currentTri].verts[0] = vertices[v1];
    tris[currentTri].verts[1] = vertices[v2];
    tris[currentTri].verts[2] = vertices[v3];
    scene->total_tris++;
    currentMesh->tris[currentMesh->n++] = tris[currentTri];
    currentTri++;
  } else if(cmd[0]=="#") {
    fgets(cmd, 250, file); // comment - ignore whole line
  } else if(strcmp(cmd, "pushTransform") == 0) {
    pushMatrix(cloneMatrix(topMatrix));
    if(currentMesh->n > 0) {
      scene->n++;
      currentMesh = &scene->meshes[scene->n];
    }
  } else if(strcmp(cmd, "popMatrix") == 0) {
    popMatrix();
    if(currentMesh->n > 0) {
      scene->n++;
      currentMesh = &scene->meshes[scene->n];
    }
  } else if(strcmp(cmd, "scale") == 0) {
    float scaleFactors[3];
    fscanf(file, "%f %f %f", scaleFactors[0], scaleFactors[1], scaleFactors[2]);
    MAT *top = topMatrix();
    top = scale(top, scaleFactors);
  } else if(strcmp(cmd, "translate") == 0) {
    float dx,dy,dz;
    fscanf(file, "%f %f %f", &dx, &dy, &dz);
    MAT *top = topMatrix();
    top = translate(top, dx, dy, dz);
  } else if(strcmp(cmd, "rotate") == 0) {
    float rx, ry, rz;
    fscanf(file, "%f %f %f", &rx, &ry, &rz);
    MAT *top = topMatrix();
    top = rotate(top, rx, ry, rz);
  } else if(strcmp(cmd, "camera") == 0) {
    float fromx, fromy, fromz;
    float atx, aty, atz;
    float upx, upy, upz;
    float fovy;
    // TODO
  } else if(strcmp(cmd, "ambient") == 0) {
    // TODO
  }

  return scene;
}



