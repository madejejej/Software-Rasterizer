#include <math.h>
#include "stdio.h"
#include "transformations.h"
#include "../matrix/matrix.h"

MAT* scale(MAT *obj, float s1, float s2, float s3){
	MAT *scaleMatrix;
	scaleMatrix = m_get(4, 4);
	m_zero(scaleMatrix);
	scaleMatrix->me[0][0] = s1;
	scaleMatrix->me[1][1] = s2;
	scaleMatrix->me[2][2] = s3;
	scaleMatrix->me[3][3] = 1;
	m_mlt_self_left(obj, scaleMatrix);
	M_FREE(scaleMatrix);
	return obj;
}

MAT* rotateZ(MAT *obj, float fi){
	MAT *rotateMatrix = m_get(4, 4);
	m_zero(rotateMatrix);
	rotateMatrix->me[0][0] = cos(fi);
	rotateMatrix->me[0][1] = -sin(fi);
	rotateMatrix->me[1][0] = sin(fi);
	rotateMatrix->me[1][1] = cos(fi);
	rotateMatrix->me[2][2] = 1;
	rotateMatrix->me[3][3] = 1;
	m_mlt_self_left(obj, rotateMatrix);
	M_FREE(rotateMatrix);
	return obj; 
}

MAT* rotateX(MAT *obj, float fi){
	MAT *rotateMatrix = m_get(4,4);
	m_zero(rotateMatrix);
	rotateMatrix->me[0][0] = 1;
	rotateMatrix->me[1][1] = cos(fi);
	rotateMatrix->me[1][2] = -sin(fi);
	rotateMatrix->me[2][1] = sin(fi);
	rotateMatrix->me[2][2] = cos(fi);
	rotateMatrix->me[3][3] = 1;
	m_mlt_self_left(obj, rotateMatrix);
	M_FREE(rotateMatrix);
	return obj; 
}

MAT* rotateY(MAT *obj, float fi){
	MAT *rotateMatrix = m_get(4,4);
	m_zero(rotateMatrix);
	rotateMatrix->me[0][0] = cos(fi);
	rotateMatrix->me[0][2] = sin(fi);
	rotateMatrix->me[1][1] = 1;
	rotateMatrix->me[2][0] = -sin(fi);
	rotateMatrix->me[2][2] = cos(fi);
	rotateMatrix->me[3][3] = 1;
	m_mlt_self_left(obj, rotateMatrix);
	M_FREE(rotateMatrix);
	return obj; 
}

MAT *rotate(MAT *obj, float degrees, vec3_t axis) {
  float theta = M_PI/180.0 * degrees;
  float s = sin(theta);
  float c = cos(theta);
  float x = axis.x, y=axis.y, z=axis.z;
  MAT *rotationMatrix = m_get_ident(4);

  rotationMatrix->me[0][0] = c + (1-c)*x*x;
  rotationMatrix->me[0][1] = (1-c)*x*y - s*z; 
  rotationMatrix->me[0][2] = (1-c)*x*z + s*y; 

  rotationMatrix->me[1][0] = (1-c)*x*y + s*z; 
  rotationMatrix->me[1][1] = c + (1-c)*y*y;
  rotationMatrix->me[1][2] = (1-c)*y*z - s*x; 

  rotationMatrix->me[2][0] = (1-c)*x*z - s*y; 
  rotationMatrix->me[2][1] = (1-c)*y*z + s*x; 
  rotationMatrix->me[2][2] = c + (1-c)*z*z;
  m_mlt_self_left(obj, rotationMatrix);
  return obj;
}

MAT* translate(MAT* obj, float xt, float yt, float zt){
    MAT *translationMatrix = m_get_ident(4);
    translationMatrix->me[0][3] = xt;
    translationMatrix->me[1][3] = yt;
    translationMatrix->me[2][3] = zt;
    print_mat(translationMatrix);
    m_mlt_self_left(obj, translationMatrix);
  	M_FREE(translationMatrix);
	  return obj; 
}

/*
void print_mat(MAT *obj){
    printf("%f %f %f\n", obj->me[0][0], obj->me[0][1], obj->me[0][2]);
    printf("%f %f %f\n", obj->me[1][0], obj->me[1][1], obj->me[1][2]);
    printf("%f %f %f\n", obj->me[2][0], obj->me[2][1], obj->me[2][2]);
}
*/

/*int main(int argc, char **arv) {
    MAT *obj = m_get(3,3);
    m_zero(obj);
    obj->me[0][0] = 1;
    obj->me[1][1] = 1;
    obj->me[2][2] = 1;
    double a = 3;
    double s[3] = {a,a,a};
    MAT *obj = scale(obj, s);
    printf("Scale:");
    print_mat(obj);
    M_FREE(obj);
    obj = rotateZ(obj, 90.0);
    printf("Rotate Z:");
    print_mat(obj);
    M_FREE(obj);
    obj = rotateX(obj, 90.0);
    printf("Rotate X:");
    print_mat(obj);
    M_FREE(obj);
    obj = rotateY(obj, 90.0);
    printf("Rotate Y:");
    print_mat(obj);
    M_FREE(obj);
    return 0;
}*/

