#include "../matrix/matrix.h"
#include "../vec.h"

MAT* getViewportTransformation(float nx,float ny);

MAT* getOrthographicProjection(float l,float r,float b,float t,float n,float f);

MAT* lookAt(vec3_t eye, vec3_t center, vec3_t up);

MAT* getPerspectiveProjection(float n, float r, float l, float t, float b, float f);


