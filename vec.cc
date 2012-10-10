#include "vec.h"

#include <stdlib.h>

static inline real frand(real v)
{
  return ((real)rand() / RAND_MAX) * v;
}

std::ostream& operator<<(std::ostream& s, const vec3& v)
{
  s << v[0] << "," << v[1] << "," << v[2];
  return s;
}

vec3 vec3_cross(const vec3& a, const vec3& b)
{
  return vec3(a[1]*b[2] - a[2]*b[1],
	      a[2]*b[0] - a[0]*b[2],
	      a[0]*b[1] - a[1]*b[0]);
}

vec3 vec3_rand(real v)
{
  return vec3(frand(v), frand(v), frand(v));
}

vec3 operator*(const real& d, const vec3& v)
{
  vec3 ret(v);
  return ret*=d;
}

vec3 operator/(const real& d, const vec3& v)
{
  vec3 ret(v);
  return ret/=d;
}

vec3 operator+(const real& d, const vec3& v)
{
  vec3 ret(v);
  return ret+=d;
}

vec3 operator-(const real& d, const vec3& v)
{
  vec3 ret(v);
  return ret-=d;
}

