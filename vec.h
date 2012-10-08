// -*- c++ -*-
#ifndef VEC_H
#define VEC_H

#include "tml.h"

#include <assert.h>
#include <ostream>

typedef double real;

class vec3
{
public:

  vec3() { data[0] = data[1] = data[2] = 0.; }

  vec3(real x, real y, real z) { data[0] = x; data[1] = y; data[2] = z; }

  vec3(const Value& v) { assert(v.isArray() && v.size() == 3); data[0] = v(0); data[1] = v(1); data[2] = v(2); }

  const real& operator[](int i) const { assert(i>=0 && i<3); return data[i]; }
  real& operator[](int i) { assert(i>=0 && i<3); return data[i]; }

private:

  real data[3];
};

std::ostream& operator<<(std::ostream& s, vec3 v);

#endif
