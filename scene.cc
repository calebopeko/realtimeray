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

Color Scene::render(int px, int py, const vec3& r) const
{
  vec3 start = camera.position;
  const real s = std::min(sizeX, sizeY);
  vec3 aim = start + camera.forward + (px - sizeX/2)/s*camera.left + (sizeY/2 - py)/s*camera.up + r;
  vec3 direction = (aim-start).normalize();
  return Scene::shade(start, direction);
}

TraceResult Scene::trace(const vec3& start, const vec3& direction) const
{
  TraceResult result;
  for ( ObjectList::const_iterator i = objects.begin(); i != objects.end(); ++i ) {
    TraceResult trace = (*i)->trace(start, direction);
    if ( trace > SMALL_NUMBER && trace < result ) result = trace;
  }
  return result;
}

Color Scene::shade(const vec3& start, const vec3& direction) const
{
  TraceResult result = trace(start, direction);
  if ( result.object ) {
    Material material = result.object->getMaterial(result.position);
    Color c = material.ambient;
    const vec3 r = vec3_rand(1.0);
    for ( LightList::const_iterator i = lights.begin(); i != lights.end(); ++i ) {
      Light& light = **i;
      const vec3 d = light.position + r - result.position;
      const real dist = d.length();
      const vec3 v = d/dist;
      const real intensity = light.intensity/dist/dist;
      const real cosi = std::max(0.,v*result.normal);
      if ( cosi > 0 && trace(result.position, v).distance > dist ) {
	c += intensity*(material.diffuse*light.color*cosi +
			material.specular*light.color*(material.specularity + 2)/(2*M_PI)*std::pow(cosi, material.specularity));
      }
    }
    return c;
  } else {
    return Color();
  }
}
