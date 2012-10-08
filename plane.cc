#include "plane.h"

Plane::Plane(Value& v)
{ 
  position = vec3(v("position"));
  normal = vec3(v("normal"));
  color = Color(v("color"));
  console::out() << "Created plane with position=" << position << " and normal=" << normal << std::endl;
}
