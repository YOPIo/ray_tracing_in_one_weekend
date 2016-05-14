#ifndef SPHERE_H
#define SPHERE_H

#include "geometry.h"
#include "material.h"

namespace ray_tracing_weekend
{

class Sphere : public Geometry
{
 public:
  Sphere() {}

  Sphere(const Vector3& center,
         const float    radius,
         Material*      material) :
      center_(center),
      radius_(radius),
      material_(material)
  {}

  ~Sphere() {}

  bool IsIntersect(const Ray&   ray,
                   const float  t_min,
                   const float  t_max,
                   HitRecord*   hit_record) const
  {
    Vector3 oc = ray.origin_ - center_;

    float a = Dot(ray.direction_, ray.direction_);
    float b = Dot(oc, ray.direction_);
    float c = Dot(oc, oc) - radius_ * radius_;

    float discriminant = b * b - a * c;

    if( discriminant > 0 )
    {
      float temp = (-b - sqrt(b * b - a * c)) / a;
      if( t_min < temp && temp < t_max )
      {
        hit_record->t_        = temp;
        hit_record->position_ = ray.origin_ + temp * ray.direction_;
        hit_record->normal_   = (hit_record->position_ - center_) / radius_;
        hit_record->material_ = material_;
        return true;
      }
      temp = (-b + sqrt(b * b - a * c)) / a;
      if( t_min < temp && temp < t_max )
      {
        hit_record->t_        = temp;
        hit_record->position_ = ray.origin_ + temp * ray.direction_;
        hit_record->normal_   = (hit_record->position_ - center_) / radius_;
        hit_record->material_ = material_;
        return true;
      }
    }
    return false;
  }

 private:
  Vector3   center_;
  float     radius_;
  Material* material_;
};

}

#endif // SPHERE_H
