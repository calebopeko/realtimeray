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

Color Scene::render(int px, int py)
{
  vec3 start = camera.position;
  vec3 aim = start + camera.forward + (px - sizeX/2)/(real)sizeX*camera.left + (sizeY/2 - py)/(real)sizeY*camera.up;
  vec3 direction = (aim-start).normalize();
  return Scene::shade(start, direction);
}

TraceResult Scene::trace(const vec3& start, const vec3& direction)
{
  TraceResult result;
  for ( ObjectList::const_iterator i = objects.begin(); i != objects.end(); ++i ) {
    TraceResult trace = (*i)->trace(start, direction);
    // if ( trace < result ) result = trace;
    if ( trace > SMALL_NUMBER && trace < result ) result = trace;
  }
  return result;
}

Color Scene::shade(const vec3& start, const vec3& direction)
{
  TraceResult result = trace(start, direction);
  if ( result.object ) {
    Color c;
    for ( LightList::const_iterator i = lights.begin(); i != lights.end(); ++i ) {
      Light& light = **i;
      const vec3 d = light.position - result.position;
      const real dist = d.length();
      const vec3 v = d/dist;
      if ( trace(result.position, v).distance > dist ) {
	c += result.object->getMaterial(result.position).color * light.color * std::max(0.,v*result.normal);
      }
    }
    return c;
  } else {
    return Color();
  }
}
