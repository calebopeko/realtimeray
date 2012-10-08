#include "sphere.h"

Sphere::Sphere(Value& v)
{ 
  center = vec3(v("center"));
  radius = v("radius");
  color = Color(v("color"));
  console::out() << "Created sphere with center=" << center << " and radius=" << radius << std::endl;
}
