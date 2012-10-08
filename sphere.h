// -*- c++ -*-
#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "color.h"

class Sphere
  : public Object
{
public:

  Sphere(Value& v);

private:

  vec3 center;

  real radius;

  Color color;
};

class SphereBuilder
  : public ObjectBuilder
{
public:

  virtual Object* build(Value& v) { return new Sphere(v); }
};

#endif
