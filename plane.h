// -*- c++ -*-
#ifndef PLANE_H
#define PLANE_H

#include "object.h"
#include "color.h"

class Plane
  : public Object
{
public:

  Plane(Value& v);

  virtual TraceResult trace(const vec3& position, const vec3& direction);

  virtual Material getMaterial(const vec3& position) { return material; }

private:

  vec3 position, normal;

  real d;

  Material material;
};

class PlaneBuilder
  : public ObjectBuilder
{
public:

  virtual Object* build(Value& v) { return new Plane(v); }
};

#endif

