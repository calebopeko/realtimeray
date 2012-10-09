// -*- c++ -*-
#ifndef LIGHT_H
#define LIGHT_H

#include "vec.h"
#include "color.h"

class Light
{
public:
  
  Light() {}

  Light(const Value& v);

  vec3 position;

  Color color;
};

#endif
