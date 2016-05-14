#ifndef MATERIAL_H
#define MATERIAL_H

#include "hit_record.h"
#include "ray.h"
#include "sample.h"
#include "vector.h"

namespace ray_tracing_weekend
{

class Material
{
 public:
  Material() {}

  virtual ~Material() {}

  virtual bool Scatter(const Ray&       ray_in,
                       const HitRecord& hit_record,
                       Vector3*         attenuation,
                       Ray*             scattered) const = 0;

};

class Lambert : public Material
{
 public:
  Lambert() {}

  Lambert(const Vector3& albedo) :
      albedo_(albedo)
  {}

  ~Lambert() {}

  inline bool Scatter(const Ray&        ray_in,
                      const HitRecord&  hit_record,
                      Vector3*          attenuation,
                      Ray*              scattered) const
  {
    Vector3 tangent = hit_record.position_ + hit_record.normal_ + Sample::UnitSphere();
    *scattered      = Ray(hit_record.position_, tangent - hit_record.position_);
    *attenuation    = albedo_;
    return true;
  }

 private:
  Vector3 albedo_;
};

class Metal : public Material
{
 public:
  Metal() {}

  Metal(const Vector3& albedo,
        const float    fuzziness) :
      albedo_(albedo),
      fuzziness_(fuzziness)
  {}

  ~Metal() {}

  inline Vector3 Reflect(const Vector3& in,
                         const Vector3& normal) const
  {
    return in - 2.f * Dot(in, normal) * normal;
  }

  inline bool Scatter(const Ray&        ray_in,
                      const HitRecord&  hit_record,
                      Vector3*          attenuation,
                      Ray*              scattered) const
  {
    Vector3 next_ray_direction = Reflect(ray_in.direction_, hit_record.normal_);
    // 完全鏡面にしたい場合は fuzziness_ * Sample::UnitSphere() を消す
    *scattered = Ray(hit_record.position_, next_ray_direction + fuzziness_ * Sample::UnitSphere());
    *attenuation = albedo_;
    return Dot( scattered->direction_, hit_record.normal_ ) > 0;
  }

 private:
  Vector3 albedo_;
  float   fuzziness_;
};

class Glass : public Material
{
 public:
  Glass() {}

  Glass(float index_of_refraction) :
      index_of_refraction_(index_of_refraction)
  {}

  ~Glass() {}

  inline Vector3 Reflect(const Vector3& in,
                         const Vector3& normal) const
  {
    return in - 2.f * Dot(in, normal) * normal;
  }

  inline bool Refract(const Vector3& in,
                      const Vector3& normal,
                      const float    index_of_refraction,
                      Vector3*       refracted_direction) const
  {
    Vector3 unit_ray_direction = Normalize(in);
    float   dt = Dot(unit_ray_direction, normal);
    float   discriminant = 1.f - (index_of_refraction * index_of_refraction) * (1.f - dt * dt);

    if( discriminant >  0 )
    {
      *refracted_direction = index_of_refraction * unit_ray_direction - normal * (index_of_refraction * dt + sqrt(discriminant));
      return true;
    }
    else
    {
      return false;
    }
  }

  bool Scatter(const Ray&       ray_in,
               const HitRecord& hit_record,
               Vector3*         attenuation,
               Ray*             scattered) const
  {
    Vector3 normal, refract;
    float   refraction;

    *attenuation = Vector3(1.f, 1.f, 1.f);

    if( Dot(ray_in.direction_, hit_record.normal_) > 0 )
    {
      normal     = -hit_record.normal_;
      refraction = index_of_refraction_;
    }
    else
    {
      normal     = hit_record.normal_;
      refraction = 1.f / index_of_refraction_;
    }

    if( Refract(ray_in.direction_, normal, refraction, &refract) )
    {
      *scattered = Ray(hit_record.position_, refract);
    }
    else
    {
      *scattered = Ray(hit_record.position_, Reflect(ray_in.direction_, hit_record.normal_) );
    }
    return true;
  }

 private:
  float index_of_refraction_;
};

}

#endif // MATERIAL_H
