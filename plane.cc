#include "plane.h"

Plane::Plane(Value& v)
{ 
  position = vec3(v("position"));
  normal = vec3(v("normal"));
  d = -normal*position;
  material.color = Color(v("color"));
  console::out() << "Created plane with position=" << position << " and normal=" << normal << " (d=" << d << ")" << std::endl;
}

TraceResult Plane::trace(const vec3& start, const vec3& direction)
{
  const real denom = normal * direction;
  if ( denom == 0 ) return TraceResult();

  const real dist = - (normal*start + d)/denom;
  if ( dist > 0 ) {
    return TraceResult(start + dist*direction, normal, dist, this);
  }
  
  return TraceResult();
}
