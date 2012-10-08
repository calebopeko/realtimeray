#include "camera.h"
#include "console.h"

Camera::Camera(const Value& v)
{
  position = vec3(v("position"));
  forward = vec3(v("forward"));
  up = vec3(v("up"));
  left = vec3_cross(up, forward);

  console::out() << "Created camera at " << position << std::endl;
}
