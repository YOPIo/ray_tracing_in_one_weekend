#ifndef CAMERA_H
#define CAMERA_H

#include <random>

#include "constants.h"
#include "sample.h"
#include "vector.h"
#include "ray.h"

#include <iostream>

namespace ray_tracing_weekend
{

class Camera
{
 public:
  Camera() {}

  Camera(const Vector3& look_from,
         const Vector3& look_at,
         const Vector3& up_vector,
         const float    vfov,
         const float    aspect,
         const float    aperture,
         const float    focus_dist)
  {
    lens_radius_ = aperture / 2.f;
    float theta = vfov * kPi / 180.f;
    float half_height = tan(theta / 2.f);
    float half_width  = aspect * half_height;

    origin_ = look_from;

    w = Normalize( look_from - look_at );
    u = Normalize( Cross(up_vector, w) );
    v = Cross(w, u);

    lower_left_corner_ = origin_ - half_width * u * focus_dist - half_height * v * focus_dist- w * focus_dist;
    horizontal_ = 2.f * half_width  * focus_dist * u;
    vertical_   = 2.f * half_height * focus_dist * v;
  }

  Ray GenerateRay(const float x, const float y) const
  {
    Vector3 point  = lens_radius_ * Sample::UnitCircle();
    Vector3 offset = u * point.x_ + v * point.y_;
    return Ray(origin_ + offset, lower_left_corner_ + x * horizontal_ + y * vertical_ - origin_ - offset);
  }

  ~Camera() {}

  Vector3 origin_;
  Vector3 lower_left_corner_;
  Vector3 horizontal_;
  Vector3 vertical_;
  Vector3 u;
  Vector3 v;
  Vector3 w;
  float   lens_radius_;
};

}

#endif // CAMERA_H
