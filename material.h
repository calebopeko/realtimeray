// -*- c++ -*-
#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

struct Material
{
  Material() {}
  
  Material(const Value& v);

  Color ambient, diffuse, specular;

  real specularity;
};

#endif
