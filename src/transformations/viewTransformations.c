#include "math.h"
#include "stdio.h"
#include "../matrix/matrix.h"
#include "viewTransformations.h"
#include "../vec.h"

MAT* getViewportTransformation(float nx,float ny) {
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
    transMat->me[3][3] = 1;
    
    /*MAT* result = m_mlt(transMat, canVector);
    M_FREE(transMat);
    M_FREE(canVector);*/
    return transMat;
}

MAT* getOrthographicProjection(float l,float r,float b,float t,float n,float f){
    MAT* transMat = m_get(4,4);
    m_zero(transMat);
    transMat->me[0][0] = 2/(r-l);
    transMat->me[1][1] = 2/(t-b);
    transMat->me[2][2] = 2/(n-f);
    transMat->me[0][3] = -(r+l)/(r-l);
    transMat->me[1][3] = -(t+b)/(t-b);
    transMat->me[2][3] = -(n+f)/(n-f);
    transMat->me[3][3] = 1;
    return transMat;
}

MAT* lookAt(vec3_t eye, vec3_t center, vec3_t up) {
    vec3_t w = v3_normalize( v3_sub(eye, center) ); 
    vec3_t u = v3_cross( up, w );
    u = v3_normalize(u);
    vec3_t v = v3_cross(w, u);

    vec3_t t = v3_init( v3_dot(u,eye), v3_dot(v, eye), v3_dot(w, eye) );

    MAT* mat = m_get(4,4);
    m_zero(mat);
    mat->me[0][0] = u.x; mat->me[0][1] = u.y; mat->me[0][2] = u.z; mat->me[0][3] = -t.x;
    mat->me[1][0] = v.x; mat->me[1][1] = v.y; mat->me[1][2] = v.z; mat->me[1][3] = -t.y;
    mat->me[2][0] = w.x; mat->me[2][1] = w.y; mat->me[2][2] = w.z; mat->me[2][3] = -t.z;
    mat->me[3][3] = 1;
    return mat;
}

MAT* getPerspectiveProjection(float n, float r, float l, float t, float b, float f){
    MAT* transMat = m_get(4,4);
    m_zero(transMat); 
    transMat->me[0][0] = 2*n/(r-l);
    transMat->me[0][2] = (l+r)/(l-r);
    transMat->me[1][1] = 2*n/(t-b);
    transMat->me[1][2] = (b+t)/(b-t);
    transMat->me[2][2] = (f+n)/(n-f);
    transMat->me[2][3] = 2*f*n/(f-n);
    transMat->me[3][2] = 1;
    return transMat;
}
