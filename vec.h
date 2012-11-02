// -*- c++ -*-
#ifndef VEC_H
#define VEC_H

#include "tml.h"

#include <assert.h>
#include <ostream>
#include <cmath>

typedef double real;

const real LARGE_NUMBER = 1e10;
const real SMALL_NUMBER = 1e-5;

class vec3
{
public:

  vec3() { data[0] = data[1] = data[2] = 0.; }

  vec3(real x, real y, real z) { data[0] = x; data[1] = y; data[2] = z; }

  vec3(const Value& v) { assert(v.isArray() && v.size() == 3); data[0] = v(0); data[1] = v(1); data[2] = v(2); }

  vec3(const vec3& other) { data[0] = other.data[0]; data[1] = other.data[1]; data[2] = other.data[2]; }

  inline const vec3& operator*=(const real& v) { for (int c=0; c<3; c++ ) data[c] *= v; return *this; }
  inline const vec3& operator/=(const real& v) { for (int c=0; c<3; c++ ) data[c] /= v; return *this; }
  inline const vec3& operator+=(const real& v) { for (int c=0; c<3; c++ ) data[c] += v; return *this; }
  inline const vec3& operator-=(const real& v) { for (int c=0; c<3; c++ ) data[c] -= v; return *this; }

  inline const vec3& operator+=(const vec3& other) { for (int c=0; c<3; c++ ) data[c] += other.data[c]; return *this; }
  inline const vec3& operator-=(const vec3& other) { for (int c=0; c<3; c++ ) data[c] -= other.data[c]; return *this; }

  inline vec3 operator*(const real& v) const { vec3 ret(*this); return ret*= v; }
  inline vec3 operator/(const real& v) const { vec3 ret(*this); return ret/= v; }
  inline vec3 operator+(const real& v) const { vec3 ret(*this); return ret+= v; }
  inline vec3 operator-(const real& v) const { vec3 ret(*this); return ret-= v; }
  inline vec3 operator-() const { return *this*(-1.0); }

  inline vec3 operator+(const vec3& other) const { vec3 ret(*this); return ret+=other; }
  inline vec3 operator-(const vec3& other) const { vec3 ret(*this); return ret-=other; }

  inline real operator*(const vec3& other) const { return data[0]*other.data[0]+data[1]*other.data[1]+data[2]*other.data[2]; }

  inline real length2() const { return (*this * *this); }
  inline real length() const { return std::sqrt(length2()); }

  inline vec3 normalize() { return *this/length(); }

  inline vec3 reflect(const vec3& normal) const { const real a = (*this)*normal; return (*this) - normal*a*2.0; }

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

vec3 vec3_rand(real max=1.0);

#endif
