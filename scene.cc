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
  vec3 start = camera.position;
  vec3 aim = start + camera.forward + (px - sizeX/2)/(real)sizeX*camera.left + (sizeY/2 - py)/(real)sizeY*camera.up;
  vec3 direction = (aim-start).normalize();
  TraceResult result;
  for ( ObjectList::const_iterator i = objects.begin(); i != objects.end(); ++i ) {
    TraceResult trace = (*i)->trace(start, direction);
    if ( trace < result ) result = trace;
  }
  if ( result.object ) {
    return result.object->getMaterial(result.position).color;
  }
  return Color();
}
