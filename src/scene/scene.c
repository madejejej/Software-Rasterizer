#include "scene.h"
#include "../types.h"
#include"../transformations/viewTransformations.h"
#include"../rasterizer/rasterizer.h"
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<math.h>

unsigned int computeDepth(scene_t *scene, float depth);
color_t computeColor(fcolor_t fcolor);
triangle2d_t* scene_compute_tris_to_rasterize(scene_t *scene);


void scene_draw(scene_t *scene, bitmap_t* bmp) {
  triangle2d_t *projected_tris = scene_compute_tris_to_rasterize(scene);
  fprintf(stderr, "Total triangles on the scene: %d\n", scene->total_tris);
  rasterize(bmp, projected_tris, scene->total_tris); 
  free(projected_tris);
}

triangle2d_t* scene_compute_tris_to_rasterize(scene_t *scene) {
  int mesh_num;
  MAT *M_vpproj = m_get_ident(4);
  m_mlt_self_left(M_vpproj, scene->M_cam);
  fprintf(stderr, "Camera:\n");
  print_mat(M_vpproj);
  fprintf(stderr, "viewport:\n"); 
  print_mat(scene->M_viewport);
  fprintf(stderr, "Projection:\n");
  print_mat(scene->M_proj);
  fprintf(stderr, "Camera:\n");
  m_mlt_self_left(M_vpproj, scene->M_proj);
  fprintf(stderr, "Projection*Camera:\n");
  print_mat(M_vpproj);
  m_mlt_self_left(M_vpproj, scene->M_viewport);
  fprintf(stderr, "Viewport*Projection*Camera:\n");
  print_mat(M_vpproj);
  int tris_computed = 0;
  triangle2d_t *projected_tris = (triangle2d_t*)malloc(sizeof(triangle2d_t) * scene->total_tris);

  fprintf(stderr, "Scene has %d meshes\n", scene->n);
  for(mesh_num=0; mesh_num<scene->n; mesh_num++) {
    int tri_num;
    mesh_t current_mesh = scene->meshes[mesh_num];
    fprintf(stderr, "Mesh modelview matrix:\n");
    print_mat(current_mesh.transform);
    fprintf(stderr, "Mesh %d has %d triangles\n", mesh_num, current_mesh.n);
    for(tri_num=0; tri_num<current_mesh.n; tri_num++) {
      triangle_t current_tri = current_mesh.tris[tri_num];
      int v;
      triangle2d_t *projectedTri = &projected_tris[tris_computed];         
      point2d_t projectedPoints[3];
      for(v=0; v<3; v++) {
        MAT *currentPoint = vec_to_mat(current_tri.verts[v]);
        MAT *proj_point = m_get(4,1);
        MAT *transform = m_get(4,4);
        m_mlt(M_vpproj, current_mesh.transform, transform);
        m_mlt(transform, currentPoint, proj_point);
        projectedPoints[v].x = proj_point->me[0][0]/ proj_point->me[3][0];
        projectedPoints[v].y = proj_point->me[0][1]/ proj_point->me[3][0];
        projectedPoints[v].depth = computeDepth(scene, proj_point->me[2][0] / proj_point->me[3][0]);
        projectedPoints[v].color = computeColor(current_tri.verts[v].color);
        fprintf(stderr, "Point in modelview coords: %f %f %f %f\n", current_tri.verts[v].x, current_tri.verts[v].y, current_tri.verts[v].z, current_tri.verts[v].t);
        fprintf(stderr, "Point after transforms: %f %f %f %f\n", proj_point->me[0][0], proj_point->me[1][0], proj_point->me[2][0], proj_point->me[3][0]);
        fprintf(stderr, "Point projected to: %f %f\n", projectedPoints[v].x, projectedPoints[v].y); 
      }
      projectedTri->v1 = projectedPoints[0];
      projectedTri->v2 = projectedPoints[1];
      projectedTri->v3 = projectedPoints[2];
      tris_computed++;
    }
      
  }
  M_FREE(M_vpproj);

  return projected_tris;
}


color_t computeColor(fcolor_t fcolor) {
  color_t col;
  int r = floor(255 * fcolor.r);
  int g = floor(255 * fcolor.g);
  int b = floor(255 * fcolor.b);
  col = (r << 16) + (g << 8) + b;
  return col;
}

unsigned int computeDepth(scene_t *scene, float depth) {
  fprintf(stderr, "Depth, near, far = %f, %f, %f\n", depth, scene->near, scene->far);
  fprintf(stderr, "Depth value: %u\n", (unsigned int)((depth - scene->near)/(scene->far - scene->near) * UINT_MAX));
  return (depth - scene->near)/(scene->far - scene->near) * UINT_MAX;
}
