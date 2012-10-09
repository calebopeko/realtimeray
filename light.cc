#include "light.h"
#include "console.h"

Light::Light(const Value& v)
{
  position = vec3(v("position"));
  color = Color(v("color"));
  intensity = v("intensity");

  console::out() << "Created light at " << position << " with color " << color << std::endl;
}
