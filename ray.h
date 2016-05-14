#ifndef RAY_H
#define RAY_H

#include "vector.h"

namespace ray_tracing_weekend
{

struct Ray
{
  Ray() {}

  Ray(const Vector3& origin,
      const Vector3& direction) :
      origin_(origin),
      direction_(direction)
  {}

  ~Ray() {}

  Vector3 origin_;
  Vector3 direction_;
};

}

#endif // RAY_H
