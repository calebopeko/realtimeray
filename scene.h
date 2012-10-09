// -*- c++ -*-
#ifndef SCENE_H
#define SCENE_H

#include "object.h"
#include "light.h"
#include "camera.h"

#include <list>

typedef std::list<Object*> ObjectList;
typedef std::list<Light*> LightList;

class Scene
{
public:

  Scene() {}

  void init(const std::string& path, int, int);

  Color shade(int, int);

  Camera camera;

private:

  int sizeX, sizeY;

  ObjectList objects;

  LightList lights;
};

#endif
