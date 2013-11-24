#include "math.h"
#include "stdio.h"
#include "transformations.h"

MAT* scale(MAT *obj, double* s){
	MAT *scaleMatrix;
	scaleMatrix = m_get(3, 3);
	m_zero(scaleMatrix);
	scaleMatrix->me[0][0] = s[0];
	scaleMatrix->me[1][1] = s[1];
	scaleMatrix->me[2][2] = s[2];
	MAT *result = m_get(3,3);
	m_mlt(scaleMatrix, obj, result);
	M_FREE(scaleMatrix);
	return result;
}

MAT* rotateZ(MAT *obj, double fi){
	MAT *rotateMatrix = m_get(3,3);
	m_zero(rotateMatrix);
	rotateMatrix->me[0][0] = cos(fi);
	rotateMatrix->me[0][1] = -sin(fi);
	rotateMatrix->me[1][0] = sin(fi);
	rotateMatrix->me[1][1] = cos(fi);
	rotateMatrix->me[2][2] = 1;
	MAT *result = m_get(3,3);
	m_mlt(rotateMatrix, obj, result);
	M_FREE(rotateMatrix);
	return result; 
}

MAT* rotateX(MAT *obj, double fi){
	MAT *rotateMatrix = m_get(3,3);
	m_zero(rotateMatrix);
	rotateMatrix->me[0][0] = 1;
	rotateMatrix->me[1][1] = cos(fi);
	rotateMatrix->me[1][2] = -sin(fi);
	rotateMatrix->me[2][1] = sin(fi);
	rotateMatrix->me[2][2] = cos(fi);
	MAT *result = m_get(3,3);
	m_mlt(rotateMatrix, obj, result);
	M_FREE(rotateMatrix);
	return result; 
}

MAT* rotateY(MAT *obj, double fi){
	MAT *rotateMatrix = m_get(3,3);
	m_zero(rotateMatrix);
	rotateMatrix->me[0][0] = cos(fi);
	rotateMatrix->me[0][2] = sin(fi);
	rotateMatrix->me[1][1] = 1;
	rotateMatrix->me[2][0] = -sin(fi);
	rotateMatrix->me[2][2] = cos(fi);
	MAT *result = m_get(3,3);
	m_mlt(rotateMatrix, obj, result);
	M_FREE(rotateMatrix);
	return result; 
}


void print_mat(MAT *obj){
    printf("%f %f %f\n", obj->me[0][0], obj->me[0][1], obj->me[0][2]);
    printf("%f %f %f\n", obj->me[1][0], obj->me[1][1], obj->me[1][2]);
    printf("%f %f %f\n", obj->me[2][0], obj->me[2][1], obj->me[2][2]);
}


int main(int argc, char **arv) {
    MAT *obj = m_get(3,3);
    m_zero(obj);
    obj->me[0][0] = 1;
    obj->me[1][1] = 1;
    obj->me[2][2] = 1;
    double a = 3;
    double s[3] = {a,a,a};
    MAT *result = scale(obj, s);
    printf("Scale:");
    print_mat(result);
    M_FREE(result);
    result = rotateZ(obj, 90.0);
    printf("Rotate Z:");
    print_mat(result);
    M_FREE(result);
    result = rotateX(obj, 90.0);
    printf("Rotate X:");
    print_mat(result);
    M_FREE(result);
    result = rotateY(obj, 90.0);
    printf("Rotate Y:");
    print_mat(result);
    M_FREE(result);
    return 0;
}

