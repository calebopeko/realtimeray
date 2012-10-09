#include "color.h"

std::ostream& operator<<(std::ostream& s, const Color& v)
{
  s << v[0] << "," << v[1] << "," << v[2];
  return s;
}


Color operator*(const real& d, const Color& v)
{
  Color ret(v);
  return ret*=d;
}

Color operator/(const real& d, const Color& v)
{
  Color ret(v);
  return ret/=d;
}

Color operator+(const real& d, const Color& v)
{
  Color ret(v);
  return ret+=d;
}

Color operator-(const real& d, const Color& v)
{
  Color ret(v);
  return ret-=d;
}

