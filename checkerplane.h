// -*- c++ -*-
#ifndef CHECKERPLANE_H
#define CHECKERPLANE_H

#include "object.h"
#include "color.h"

class Checkerplane
  : public Object
{
public:

  Checkerplane(Value& v);

  virtual TraceResult trace(const vec3& position, const vec3& direction);

  virtual Material getMaterial(const vec3& position);

private:

  vec3 position, normal;

  real d;

  Material material1, material2;

  vec3 orientation1, orientation2;

  real length1, length2;
};

class CheckerplaneBuilder
  : public ObjectBuilder
{
public:

  virtual Object* build(Value& v) { return new Checkerplane(v); }
};

#endif

