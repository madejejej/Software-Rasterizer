#include "scene.h"
#include "../types.h"
#include"../rasterizer/rasterizer.h"
#include<stdlib.h>
#include<math.h>

unsigned int computeDepth(scene_t *scene, float depth);
color_t computeColor(fcolor_t fcolor);
triangle2d_t* scene_compute_tris_to_rasterize(scene_t *scene);


void scene_draw(scene_t *scene, bitmap_t* bmp) {
  triangle2d_t *projected_tris = scene_compute_tris_to_rasterize(scene);
  rasterize(bmp, projected_tris, scene->total_tris); 
}

triangle2d_t* scene_compute_tris_to_rasterize(scene_t *scene) {
  int mesh_num;
  MAT *M_vpproj = m_get(4,4);
  m_mlt(scene->M_viewport, scene->M_proj, M_vpproj);
  int tris_computed = 0;
  triangle2d_t *projected_tris = (triangle2d_t*)malloc(sizeof(triangle2d_t) * scene->total_tris);

  for(mesh_num=0; mesh_num<scene->n; mesh_num++) {
    int tri_num;
    mesh_t current_mesh = scene->meshes[mesh_num];

    for(tri_num=0; tri_num<current_mesh.n; tri_num++) {
      triangle_t current_tri = current_mesh.tris[tri_num];
      int v;
      triangle2d_t projectedTri = projected_tris[tris_computed];         
      point2d_t projectedPoints[3];
      for(v=0; v<2; v++) {
        MAT *currentPoint = vec_to_mat(current_tri.verts[v]);
        MAT *proj_point = m_get(1,4);
        MAT *transform = m_get(4,4);
        m_mlt(M_vpproj, current_mesh.transform, transform);
        m_mlt(transform, currentPoint, proj_point);
        projectedPoints[v].x = proj_point->me[0][0];
        projectedPoints[v].y = proj_point->me[0][1];
        projectedPoints[v].depth = computeDepth(scene, proj_point->me[0][2]);
        projectedPoints[v].color = computeColor(current_tri.verts[v].color);
      }
      projectedTri.v1 = projectedPoints[0];
      projectedTri.v2 = projectedPoints[1];
      projectedTri.v3 = projectedPoints[2];
      tris_computed++;
    }
      
  }

  return projected_tris;
}


color_t computeColor(fcolor_t fcolor) {
  color_t col;
  int r = floor(255 * fcolor.r);
  int g = floor(255 * fcolor.g);
  int b = floor(255 * fcolor.b);
  col = (r >> 16) + (g >> 8) + b;
  return col;
}

unsigned int computeDepth(scene_t *scene, float depth) {
  return 1; // TODO implement
}
