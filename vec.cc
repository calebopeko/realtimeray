#include "vec.h"

std::ostream& operator<<(std::ostream& s, const vec3& v)
{
  s << v[0] << "," << v[1] << "," << v[2];
  return s;
}

