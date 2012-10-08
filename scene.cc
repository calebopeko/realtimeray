#include "scene.h"
#include "tml.h"

Scene::Scene(const std::string& path)
{
  Parser sceneFile(path);
  Value& fileObjects = sceneFile("objects");
  for (unsigned i = 0; i< fileObjects.size(); i++) {
    Value v = fileObjects(i);
    std::string type = v("type");
    objects.push_back(ObjectFactory::instance().build(type, v));
  }
}

void Scene::render(const std::string& file)
{
}
