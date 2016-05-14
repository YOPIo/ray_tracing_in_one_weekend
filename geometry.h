#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "hit_record.h"
#include "ray.h"
#include "vector.h"

namespace ray_tracing_weekend
{

class Geometry
{
 public:
  Geometry() {}

  virtual ~Geometry() {}

  virtual bool IsIntersect(const Ray&   ray,
                           const float  t_min,
                           const float  t_max,
                           HitRecord*   hit_record) const = 0;
};

};

#endif // GEOMETRY_H
