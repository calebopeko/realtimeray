// -*- c++ -*-
#ifndef CAMERA_H
#define CAMERA_H

#include "vec.h"

class Camera
{
public:
  
  Camera() {}

  Camera(const Value& v);

private:

  vec3 position, forward, up;
};

#endif
