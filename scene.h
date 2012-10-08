// -*- c++ -*-
#ifndef SCENE_H
#define SCENE_H

#include "object.h"

#include <list>

class Scene
{
public:

  Scene() {}

  Scene(const std::string& path);

  void render(const std::string& file);

private:

  std::list<Object*> objects;
};

#endif
