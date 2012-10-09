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
  
  virtual TraceResult trace(const vec3& position, const vec3& direction);

  virtual Material getMaterial(const vec3& position) { return material; }

private:

  vec3 center;

  real radius;

  Material material;

};

class SphereBuilder
  : public ObjectBuilder
{
public:

  virtual Object* build(Value& v) { return new Sphere(v); }
};

#endif
