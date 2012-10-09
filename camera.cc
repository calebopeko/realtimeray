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

void Camera::move(real v)
{
  position += v*forward;
}

void Camera::strafe(real v)
{
  position += v*left;
}

void Camera::climb(real v)
{
  position += v*up;
}

void Camera::yaw(real v)
{
  const real c = std::cos(v);
  const real s = std::sin(v);
  
  forward[0] = c*forward[0] + s*forward[2];
  forward[2] = -s*forward[0] + c*forward[2];

  forward = forward.normalize();
  left = vec3_cross(up, forward);
}
