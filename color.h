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

  inline const Color& operator*=(const real& v) { for (int c=0; c<3; c++ ) data[c] *= v; return *this; }
  inline const Color& operator/=(const real& v) { for (int c=0; c<3; c++ ) data[c] /= v; return *this; }
  inline const Color& operator+=(const real& v) { for (int c=0; c<3; c++ ) data[c] += v; return *this; }
  inline const Color& operator-=(const real& v) { for (int c=0; c<3; c++ ) data[c] -= v; return *this; }

  inline const Color& operator*=(const Color& other) { for (int c=0; c<3; c++ ) data[c] *= other.data[c]; return *this; }

  inline const Color& operator+=(const Color& other) { for (int c=0; c<3; c++ ) data[c] += other.data[c]; return *this; }
  inline const Color& operator-=(const Color& other) { for (int c=0; c<3; c++ ) data[c] -= other.data[c]; return *this; }

  inline Color operator*(const real& v) const { Color ret(*this); return ret*= v; }
  inline Color operator/(const real& v) const { Color ret(*this); return ret/= v; }
  inline Color operator+(const real& v) const { Color ret(*this); return ret+= v; }
  inline Color operator-(const real& v) const { Color ret(*this); return ret-= v; }

  inline Color operator*(const Color& other) const { Color ret(*this); return ret*=other; }

  inline Color operator-() const { return *this*(-1.0); }

  inline Color operator+(const Color& other) const { Color ret(*this); return ret+=other; }
  inline Color operator-(const Color& other) const { Color ret(*this); return ret-=other; }

  inline bool isZero() const { return data[0] == 0.0 && data[1] == 0.0 && data[2] == 0.0; }

private:

  real data[3];
};

Color operator*(const real& d, const Color& v);
Color operator/(const real& d, const Color& v);
Color operator+(const real& d, const Color& v);
Color operator-(const real& d, const Color& v);

std::ostream& operator<<(std::ostream& s, const Color& v);

#endif
