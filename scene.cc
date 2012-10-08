#include "scene.h"
#include "tml.h"

void Scene::init(const std::string& path, int sx, int sy)
{
  sizeX = sx; sizeY = sy;

  Parser sceneFile(path);
  Value& fileObjects = sceneFile("objects");
  for (unsigned i = 0; i< fileObjects.size(); i++) {
    Value v = fileObjects(i);
    std::string type = v("type");
    objects.push_back(ObjectFactory::instance().build(type, v));
  }

  Value fileLights = sceneFile("lights");
  for (unsigned i = 0; i< fileLights.size(); i++) {
    lights.push_back(new Light(fileLights(i)));
  }

  camera = Camera(sceneFile("camera"));
}

Color Scene::shade(int px, int py)
{
  return Color(1., 0., 0.);
}
