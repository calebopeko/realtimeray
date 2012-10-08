// -*- c++ -*-
#ifndef COLOR_H
#define COLOR_H

#include "vec.h"

class Color
{
public:

  Color() { data[0] = data[1] = data[2] = 0.; }

  Color(real x, real y, real z) { data[0] = x; data[1] = y; data[2] = z; }

  Color(const Value& v) { assert(v.isArray() && v.size() == 3); data[0] = v(0); data[1] = v(1); data[2] = v(2); }

  const real& operator[](int i) const { assert(i>=0 && i<3); return data[i]; }
  real& operator[](int i) { assert(i>=0 && i<3); return data[i]; }

private:

  real data[3];
};

std::ostream& operator<<(std::ostream& s, const Color& v);

#endif
