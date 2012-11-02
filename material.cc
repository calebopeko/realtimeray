#include "material.h"
#include "console.h"

Material::Material(const Value& v)
{
  ambient = Color(v("ambient"));
  diffuse = Color(v("diffuse"));
  specular = Color(v("specular"));
  specularity = v("specularity");
  reflect = Color(v("reflect"));
}
