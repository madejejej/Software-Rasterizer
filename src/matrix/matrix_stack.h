#ifndef __MATRIX__STACK_H__
#define __MATRIX__STACK_H__
#include"matrix.h"


void initMatrixStack();
MAT* topMatrix();
MAT* popMatrix();
void pushMatrix(MAT* matrix);

#endif
