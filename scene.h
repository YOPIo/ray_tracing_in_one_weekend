#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "geometry.h"
#include "hit_record.h"
#include "ray.h"
#include "vector.h"

#include <iostream>

namespace ray_tracing_weekend
{

class Scene
{
 public:
  Scene() {}

  Scene(Geometry** geometries,
        int        size) :
      geometries_(geometries),
      size_(size)
  {}

  ~Scene() {}

  bool IntersectGeometry(const Ray&  ray,
                         const float t_min,
                         const float t_max,
                         HitRecord*  hit_record) const
  {
    HitRecord temp_hit_record;
    bool      hit_anything = false;
    float     t = t_max;
    for(int i = 0; i < size_; ++i)
    {
      if( geometries_[i]->IsIntersect(ray, t_min, t, &temp_hit_record) )
      {
        hit_anything = true;
        t            = temp_hit_record.t_;
        *hit_record  = temp_hit_record;
      }
    }
    return hit_anything;
  }

 private:
  Geometry** geometries_;
  int        size_;
};

}

#endif // SCENE_H
