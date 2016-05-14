#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "vector.h"

namespace ray_tracing_weekend
{

class Material;

struct HitRecord
{
  float     t_;
  Vector3   position_;
  Vector3   normal_;
  Material* material_;
};

}

#endif // HIT_RECORD_H
