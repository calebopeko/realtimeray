// -*- c++ -*-
#ifndef CAMERA_H
#define CAMERA_H

#include "vec.h"

class Camera
{
public:
  
  Camera() {}

  Camera(const Value& v);

  vec3 position, forward, up, left;

  void move(real v);
  
  void strafe(real v);
  
  void yaw(real v);

private:

};

#endif
