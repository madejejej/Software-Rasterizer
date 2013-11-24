#include "matrix.h"
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
   double *buff = malloc(sizeof(double)*m*n);
   matrix ->me = malloc(m*sizeof(double*));
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



MAT	*m_mlt(const MAT *A, const MAT *B, MAT *OUT)
{
	unsigned int	i, j,  k, m, n, p;
	double **A_v, **B_v, sum;

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


