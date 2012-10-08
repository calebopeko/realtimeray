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

class ObjectBuilder
{
public:

  virtual Object* build(Value& v) = 0;
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
