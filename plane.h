// -*- c++ -*-
#ifndef PLANE_H
#define PLANE_H

#include "object.h"
#include "vec.h"

class Plane
  : public Object
{
public:

  Plane(Value& v);

private:

  vec3 position, normal;
};

class PlaneBuilder
  : public ObjectBuilder
{
public:

  virtual Object* build(Value& v) { return new Plane(v); }
};

#endif
