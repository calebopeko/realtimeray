// -*- c++ -*-
#ifndef OBJECT_H
#define OBJECT_H

#include "tml.h"
#include "console.h"

class Object
{
public:

  Object() {}

};

class Plane
  : public Object
{
public:

  Plane(Value& v) { console::out() << "type=" << v("type") << " should be 'plane'" << std::endl; }
};

class Sphere
  : public Object
{
public:

  Sphere(Value& v) { console::out() << "type=" << v("type") << " should be 'sphere'" << std::endl; }
};



class ObjectBuilder
{
public:

  virtual Object* build(Value& v) = 0;
};

class PlaneBuilder
  : public ObjectBuilder
{
public:

  virtual Object* build(Value& v) { return new Plane(v); }
};

class SphereBuilder
  : public ObjectBuilder
{
public:

  virtual Object* build(Value& v) { return new Sphere(v); }
};

class ObjectFactory
{
 public:

  ObjectFactory();

  ~ObjectFactory();

  static ObjectFactory& instance() { return instance_; }

  Object* build(const std::string& type, Value& v) { return builders[type]->build(v); }

 private:

  static ObjectFactory instance_;

  std::map<std::string, ObjectBuilder*> builders;
};

#endif
