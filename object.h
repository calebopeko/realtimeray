// -*- c++ -*-
#ifndef OBJECT_H
#define OBJECT_H

#include "tml.h"
#include "console.h"
#include "trace.h"
#include "material.h"

class Object
{
public:

  Object() {}

  virtual TraceResult trace(const vec3& position, const vec3& direction) = 0;

  virtual Material getMaterial(const vec3& position)  = 0;

};

class ObjectBuilder
{
public:

  virtual Object* build(Value& v) = 0;

  virtual ~ObjectBuilder() {}
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
