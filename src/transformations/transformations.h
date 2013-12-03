#include "../matrix/matrix.h"

MAT* scale(MAT *obj, float s1, float s2, float s3);
MAT* rotateZ(MAT *obj, float fi);
MAT* rotateX(MAT *obj, float fi);
MAT *rotate(MAT *obj, float rx, float ry, float rz); 
MAT* rotateY(MAT *obj, float fi);
MAT* translate(MAT* obj, float xt, float yt, float zt);
