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

  Scene() {}

  void init(const std::string& path, int, int);

  Color shade(int, int);

private:

  int sizeX, sizeY;

  Camera camera;

  std::list<Object*> objects;

  std::list<Light*> lights;
};

#endif
