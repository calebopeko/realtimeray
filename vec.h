// -*- c++ -*-
#ifndef VEC_H
#define VEC_H

#include "tml.h"

#include <assert.h>
#include <ostream>
#include <cmath>

typedef double real;

class vec3
{
public:

  vec3() { data[0] = data[1] = data[2] = 0.; }

  vec3(real x, real y, real z) { data[0] = x; data[1] = y; data[2] = z; }

  vec3(const Value& v) { assert(v.isArray() && v.size() == 3); data[0] = v(0); data[1] = v(1); data[2] = v(2); }

  vec3(const vec3& other) { data[0] = other.data[0]; data[1] = other.data[1]; data[2] = other.data[2]; }

  const vec3& operator*=(const real& v) { for (int c=0; c<3; c++ ) data[c] *= v; return *this; }
  const vec3& operator/=(const real& v) { for (int c=0; c<3; c++ ) data[c] /= v; return *this; }
  const vec3& operator+=(const real& v) { for (int c=0; c<3; c++ ) data[c] += v; return *this; }
  const vec3& operator-=(const real& v) { for (int c=0; c<3; c++ ) data[c] -= v; return *this; }

  const vec3& operator+=(const vec3& other) { for (int c=0; c<3; c++ ) data[c] += other.data[c]; return *this; }
  const vec3& operator-=(const vec3& other) { for (int c=0; c<3; c++ ) data[c] -= other.data[c]; return *this; }

  vec3 operator*(const real& v) const { vec3 ret(*this); return ret*= v; }
  vec3 operator/(const real& v) const { vec3 ret(*this); return ret/= v; }
  vec3 operator+(const real& v) const { vec3 ret(*this); return ret+= v; }
  vec3 operator-(const real& v) const { vec3 ret(*this); return ret-= v; }

  vec3 operator+(const vec3& other) const { vec3 ret(*this); return ret+=other; }
  vec3 operator-(const vec3& other) const { vec3 ret(*this); return ret-=other; }

  real operator*(const vec3& other) { return data[0]*other.data[0]+data[1]*other.data[1]+data[2]*other.data[2]; }

  real length() { return std::sqrt(*this * *this); }

  const real& operator[](int i) const { assert(i>=0 && i<3); return data[i]; }
  real& operator[](int i) { assert(i>=0 && i<3); return data[i]; }

private:

  real data[3];
};

std::ostream& operator<<(std::ostream& s, const vec3& v);

vec3 operator*(const real& d, const vec3& v);
vec3 operator/(const real& d, const vec3& v);
vec3 operator+(const real& d, const vec3& v);
vec3 operator-(const real& d, const vec3& v);

vec3 vec3_cross(const vec3& a, const vec3& b);

#endif
