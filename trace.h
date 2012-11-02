// -*- c++ -*-
#ifndef TRACE_H
#define TRACE_H

#include "vec.h"

class Object;

struct TraceResult
{
  TraceResult()
    : position(), normal(), distance(LARGE_NUMBER), object(NULL) {}

  TraceResult(const vec3& pos, const vec3& n, real d, Object* o)
    : position(pos), normal(n), distance(d), object(o) {}

  vec3 position, normal;
  
  real distance;

  Object* object;

  inline bool operator<(const TraceResult& other) const { return distance < other.distance; }
  inline bool operator>(const TraceResult& other) const { return distance > other.distance; }
  inline bool operator<(const real& other) const { return distance < other; }
  inline bool operator>(const real& other) const { return distance > other; }
};

#endif
