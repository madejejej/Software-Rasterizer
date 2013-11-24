#include "../matrix/matrix.h"

MAT* getViewportTransformation(double nx,double ny,double nz,double widthScreen, double heightScreen);

MAT* getOrthographicProjection(double l,double r,double b,double t,double n,double f)

MAT* getCameraProjection(MAT *obj,double xe,double ye,double ze)

MAT* getPerspectiveProjection(double n, double r, double l, double t, double b, double f)


