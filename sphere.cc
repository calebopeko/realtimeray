#include "sphere.h"

Sphere::Sphere(Value& v)
{ 
  center = vec3(v("center"));
  radius = v("radius");
  material.color = Color(v("color"));
  console::out() << "Created sphere with center=" << center << " and radius=" << radius << std::endl;
}

TraceResult Sphere::trace(const vec3& start, const vec3& direction)
{
  const real d2 = direction*direction;
  const real p = (start - center)*direction/d2;
  const real q = ((start - center)*(start - center) - radius*radius)/d2;
  const real radic = p*p - q;
  if ( radic < 0 ) return TraceResult();
  const real sradic = std::sqrt(radic);
  const real dist1 = -p + sradic;
  const real dist2 = -p - sradic;
  
  const real distMin = std::min(dist1, dist2);
  const real distMax = std::max(dist1, dist2);
  if ( distMax < 0 ) return TraceResult();
  if ( distMin > 0 ) {
    const vec3 hit = start + distMin*direction;
    const vec3 normal = (hit-center).normalize();
    return TraceResult(hit, normal, distMin, this);
  }
  const vec3 hit = start + distMax*direction;
  const vec3 normal = (hit-center).normalize();
  return TraceResult(hit, normal, distMax, this);
}
