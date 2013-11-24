#include "math.h"
#include "stdio.h"
#include "viewTransformations.h"

MAT* getViewportTransformation(double nx,double ny,double nz,double widthScreen, double heightScreen){
    /*MAT* canVector = m_get(4,1);
    canVector->me[0][0] = xCanonical;
    canVector->me[0][1] = yCanonical;
    canVactor->me[0][2] = zCanonical;
    canVactor->me[0][3] = 1;*/
    
    MAT* transMat = m_get(4,4);
    m_zero(transMat);
    transMat->me[0][0] = nx/2;
    transMat->me[0][3] = (nx-1)/2;
    transMat->me[1][1] = ny/2;
    transMat->me[1][3] = (ny-1)/2;
    transMat->me[2][2] = 1;
    transMat->me[3][4] = 1;
    
    /*MAT* result = m_mlt(transMat, canVector);
    M_FREE(transMat);
    M_FREE(canVector);*/
    return transMat;
}

MAT* getOrthographicProjection(double l,double r,double b,double t,double n,double f){
    MAT* transMat = m_get(4,4);
    m_zero(transMat);
    transMat->me[0][0] = 2/(r-l);
    transMat->me[1][1] = 2/(t-b);
    transMat->me[2][2] = 2/(n-f);
    transMat->me[0][3] = -(r+l)/(r-l);
    transMat->me[1][3] = -(t+b)/(t-b);
    transMat->me[2][3] = -(n+f)(n-f);
    transMat->me[3][3] = 1;
    return transMat;
}

MAT* getCameraProjection(MAT *obj,double xe,double ye,double ze){
    MAT* tmp = mget(4,4);
    m_zero(tmp);
    tmp->me[0][0] = 1;
    tmp->me[1][1] = 1;
    tmp->me[2][2] = 1;
    tmp->me[3][3] = 1;
    tmp->me[0][3] = -xe;
    tmp->me[1][3] = -ye;
    tmp->me[2][3] = -ze;
    return m_mlt(obj, tmp);
}

MAT* getPerspectiveProjection(double n, double r, double l, double t, double b, double f){
    MAT* transMat = mget(4,4);
    m_zero(tmp);
    transMat->me[0][0] = 2*n/(r-l);
    transMat->me[0][2] = (l+r)/(l-r);
    transMat->me[1][1] = 2*n/(t-b);
    transMat->me[1][2] = (b+t)/(b-t);
    transMat->me[2][2] = (f+n)/(n-f);
    transMat->me[2][3] = 2*f*n/(f-n);
    transMat->me[3][2] = 1;
    return transMat;
}