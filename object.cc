#include "object.h"

ObjectFactory ObjectFactory::instance_;

ObjectFactory::ObjectFactory()
{
  builders["plane"] = new PlaneBuilder();
  builders["sphere"] = new SphereBuilder();
}

ObjectFactory::~ObjectFactory()
{
  for ( std::map<std::string, ObjectBuilder*>::iterator i=builders.begin(); i!=builders.end(); ++i ) {
    delete i->second;
  }
}
