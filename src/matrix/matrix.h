
typedef	struct	{
		unsigned int	m, n;
		double	**me;	
} MAT;

MAT	*m_get(int m, int n);
MAT	*m_zero(MAT *A);
MAT	*m_mlt(const MAT *A, const MAT *B, MAT *OUT);
MAT *m_get_ident(int m);
