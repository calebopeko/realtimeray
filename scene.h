// -*- c++ -*-
#ifndef SCENE_H
#define SCENE_H

#include "object.h"
#include "light.h"
#include "camera.h"

#include <list>

class Scene
{
public:

  Scene(const std::string& path);

  void render(const std::string& file);

private:

  Camera camera;

  std::list<Object*> objects;

  std::list<Light*> lights;
};

#endif
