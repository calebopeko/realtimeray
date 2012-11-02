#include "object.h"
#include "plane.h"
#include "sphere.h"
#include "checkerplane.h"

ObjectFactory ObjectFactory::instance_;

ObjectFactory::ObjectFactory()
{
  builders["plane"] = new PlaneBuilder();
  builders["sphere"] = new SphereBuilder();
  builders["checkerplane"] = new CheckerplaneBuilder();
}

ObjectFactory::~ObjectFactory()
{
  for ( std::map<std::string, ObjectBuilder*>::iterator i=builders.begin(); i!=builders.end(); ++i ) {
    delete i->second;
  }
}
