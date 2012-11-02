#include "checkerplane.h"

Checkerplane::Checkerplane(Value& v)
{ 
  position = vec3(v("position"));
  normal = vec3(v("normal"));
  orientation1 = vec3(v("orientation1"));
  orientation2 = vec3(v("orientation2"));
  length1 = orientation1.length2();
  length2 = orientation2.length2();
  d = -normal*position;
  material1 = Material(v("material1"));
  material2 = Material(v("material2"));
  console::out() << "Created checkerplane with position=" << position << " and normal=" << normal << " (d=" << d << ")" << std::endl;
}

TraceResult Checkerplane::trace(const vec3& start, const vec3& direction)
{
  const real denom = normal * direction;
  if ( denom == 0 ) return TraceResult();

  const real dist = - (normal*start + d)/denom;
  if ( dist > 0 ) {
    return TraceResult(start + dist*direction, normal, dist, this);
  }
  
  return TraceResult();
}

Material Checkerplane::getMaterial(const vec3& spot)
{
  const real u = (spot - position)*orientation1/length1;
  const real v = (spot - position)*orientation2/length2;

  if ( u-floor(u) < 0.5 ^ v-floor(v) < 0.5 ) {
    return material1;
  } else {
    return material2;
  }
}
