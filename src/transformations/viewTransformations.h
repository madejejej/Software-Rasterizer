#include "../matrix/matrix.h"

MAT* getViewportTransformation(float nx,float ny);

MAT* getOrthographicProjection(float l,float r,float b,float t,float n,float f);

MAT* getCameraProjection(MAT *obj,float xe,float ye,float ze);

MAT* getPerspectiveProjection(float n, float r, float l, float t, float b, float f);


