#include"vec.h"

#include<math.h>


vec3_t v3_init(float x, float y, float z) {
  vec3_t v;
  v.x = x; v.y = y; v.z = z;
  return v;
}

float v3_dot(vec3_t v, vec3_t w) {
  return v.x*w.x + v.y*w.y + v.z*w.z;
}

vec3_t v3_cross(vec3_t lhs, vec3_t rhs) {
  vec3_t result;
  result.x = lhs.y*rhs.z - lhs.z*rhs.y;
  result.y = lhs.z*rhs.x - lhs.x*rhs.z;
  result.z = lhs.x*rhs.y - lhs.y*rhs.x;
  return result;
}

float v3_length(vec3_t v) {
  return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

vec3_t v3_sub(vec3_t lhs, vec3_t rhs) {
  vec3_t result;
  result.x = lhs.x - rhs.x;
  result.y = lhs.y - rhs.y;
  result.z = lhs.z - rhs.z;
  return result;
}

vec3_t v3_normalize(vec3_t v) {
  vec3_t result; 
  float length = v3_length(v);
  result.x = v.x / length;
  result.y = v.y / length;
  result.z = v.z / length;
  return result;
}
