#ifndef __MATRIX_H__
#define __MATRIX_H__
#include"../types.h"
typedef	struct	{
		unsigned int	m, n;
		float **me;	
} MAT;

MAT	*m_get(int m, int n);
MAT	*m_zero(MAT *A);
MAT	*m_mlt(const MAT *A, const MAT *B, MAT *OUT);
MAT *m_get_ident(int m);
MAT *vec_to_mat(vec4_t vec);
#endif

