#ifndef __VEC_H__
#define __VEC_H__

typedef struct {
  float x,y,z;
} vec3_t;

vec3_t v3_init(float x, float y, float z);

float v3_dot(vec3_t v, vec3_t w);
float v3_length(vec3_t v);

vec3_t v3_cross(vec3_t lhs, vec3_t rhs);
vec3_t v3_sub(vec3_t lhs, vec3_t rhs);
vec3_t v3_normalize(vec3_t v); 

vec3_t v3_up(vec3_t up, vec3_t zvec); 
#endif
