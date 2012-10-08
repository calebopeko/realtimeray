#include "color.h"

std::ostream& operator<<(std::ostream& s, const Color& v)
{
  s << v[0] << "," << v[1] << "," << v[2];
  return s;
}

