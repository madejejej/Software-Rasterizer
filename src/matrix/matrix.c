#include "matrix.h"
#include"../types.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


MAT	*m_get(int m, int n)
{
   MAT	*matrix;
   int	i;
   
   if (m < 0 || n < 0)
     perror("Size cannot be negative nr");

   matrix = (MAT *) malloc(sizeof(MAT));
   if(matrix == NULL)
    perror("Initialization faild");
   matrix -> m = m;
   matrix -> n = n;
   float *buff = malloc(sizeof(float)*m*n);
   matrix ->me = malloc(m*sizeof(float*));
   for(i=0; i<m; ++i){
    matrix->me[i] = buff + i*n;
   }
   return matrix;
}

void M_FREE(MAT *A){
    free(A->me);
    free(A);
}



MAT	*m_zero(MAT *A)
{
	int	i,j, A_m, A_n;
	A_m = A->m;	A_n = A->n;
	for ( i = 0; i < A_m; i++ ){
		for ( j = 0; j < A_n; j++ ){
			A->me[i][j] = 0.0; 
	    }
    }

	return A;
}

MAT *m_get_ident(int m){
    MAT* new = m_get(m, m);
    m_zero(new);
    int i;
    for(i = 0; i<m; ++i){
        new -> me[i][i] = 1;
    }
    return new;
}

MAT *m_copy(MAT* A){
    int i, j;
    MAT *copied = m_get(A->m, A->n);
    for(i=0; i< A->m; ++i)
        for(j=0; j< A->n; ++j)
            copied->me[i][j] = A->me[i][j];
    return copied;
}


MAT	*m_mlt(const MAT *A, const MAT *B, MAT *OUT)
{
	unsigned int	i, j,  k, m, n, p;
	float **A_v, **B_v, sum;

	if ( A==(MAT *)NULL || B==(MAT *)NULL )
		perror("Matrixes cannot be null");
	if ( A->n != B->m )
		perror("Sizes do not match");
	if ( A == OUT || B == OUT )
		perror("Sizes do not match");
	m = A->m;	
	n = A->n;	
	p = B->n;
	A_v = A->me;		
	B_v = B->me;

	for ( i=0; i<m; i++ )
		for  ( j=0; j<p; j++ )
		{
			sum = 0.0;
			for ( k=0; k<n; k++ )
				sum += A_v[i][k]*B_v[k][j];
			OUT->me[i][j] = sum;
		}


	return OUT;
}

MAT *m_mlt_self_left(MAT *A, const MAT *B) {
  MAT *old = m_copy(A);
  m_mlt(B, old, A);
  return A;
}


MAT* vec_to_mat(vec4_t vec) {
  MAT *m = m_get(4,1);
  m->me[0][0] = vec.x;
  m->me[1][0] = vec.y;
  m->me[2][0] = vec.z;
  m->me[3][0] = vec.t;
  return m;
}

void print_mat(MAT *obj){
    printf("%f %f %f %f\n", obj->me[0][0], obj->me[0][1], obj->me[0][2], obj->me[0][3]);
    printf("%f %f %f %f\n", obj->me[1][0], obj->me[1][1], obj->me[1][2], obj->me[1][3]);
    printf("%f %f %f %f\n", obj->me[2][0], obj->me[2][1], obj->me[2][2], obj->me[2][3]);
    printf("%f %f %f %f\n", obj->me[3][0], obj->me[3][1], obj->me[3][2], obj->me[3][3]);
}


