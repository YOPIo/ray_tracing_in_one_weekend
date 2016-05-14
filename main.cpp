#include <iostream>

#include "camera.h"
#include "constants.h"
#include "hit_record.h"
#include "material.h"
#include "sample.h"
#include "scene.h"
#include "sphere.h"
#include "vector.h"

namespace ray_tracing_weekend
{

Scene* CreateScene()
{
  Geometry** geometries = new Geometry*[12 + 2];

  geometries[0] = new Sphere( Vector3(0, -1000.01, 0),  1000,   new Lambert( Vector3(0.35, 0.35, 0.35) ) );
  geometries[1] = new Sphere( Vector3(0.f, 1.f, 0.),     1.f,    new Metal( Vector3(0.9f, 0.9f, 0.9f), 0.2f ));

  float angle  = 0.f;
  float radius = 2.5f;
  float r = 1;
  float g = 0;
  float b = 0;
  int   n = 2;
  for(int i = 0; i < 12; angle += 30, ++i)
  {
    const float x = radius * cos(angle / 180 * kPi);
    const float z = radius * sin(angle / 180 * kPi);
    if(angle < 120)
    {
      r -= 0.25;
      g += 0.25;
    }
    else if(120 <= angle && angle < 240)
    {
      g -= 0.25;
      b += 0.25;
    }
    else if(240 <= angle)
    {
      b -= 0.25;
      r += 0.25;
    }
    /*
    if(r == 1 || g == 1 || b == 1)
    {
      const float u = 1.5 * cos((angle + 30) / 180 * kPi);
      const float v = 1.5 * sin((angle + 30)/ 180 * kPi);
      geometries[n++] = new Sphere( Vector3(u, 0.42f, v), 0.42f, new Glass(1.4));
    }
    */
    geometries[n++] = new Sphere( Vector3(x, 0.5f, z), 0.5f, new Lambert( Vector3(r, g, b) ));
  }
  return new Scene(geometries, 14);
}

Vector3 Color(const Ray& ray,
              Scene*     scene,
              int        depth)
{
  HitRecord hit_record;
  if( scene->IntersectGeometry(ray, 0.001f, kInf, &hit_record) )
  {
    Vector3   attenuation;
    Ray       scattered;
    if( hit_record.material_->Scatter(ray, hit_record, &attenuation, &scattered) )
    {
      if(depth < 50)
      {
        return attenuation * Color(scattered, scene, depth + 1);
      }
      else
      {
        return Vector3(0.f, 0.f, 0.f);
      }
    }
    else
    {
      return Vector3(0.f, 0.f, 0.f);
    }
  }
  else
  {
    Vector3 unit_ray_direction = Normalize(ray.direction_);
    float   t = 0.5f * (unit_ray_direction.y_ + 1.f);
    return (1.f - t) * Vector3(1.f, 1.f, 1.f) + t * Vector3(0.5f, 0.7f, 1.f);
  }
}

void Render()
{
  const int width   = 1920;
  const int height  = 1080;
  const int sample  = 256;

  std::cout << "P3\n" << width << " " << height << "\n255\n";

  Vector3 look_from(8.0f, 6.8f, 0.f);
  Vector3 look_at(0.f, 0.f, 0.f);
  float   aperture = 1.2f;

  Scene *scene = CreateScene();

  Camera camera( look_from,
                 look_at,
                 Vector3(0.f, 1.f, 0.f),
                 25.f,
                 static_cast<float>(width) / static_cast<float>(height),
                 aperture,
                 (look_from - Vector3(0, 1, 0)).Length() );

  for(int y = height - 1; y >= 0; --y)
  {
    for(int x = 0; x < width; ++x)
    {
      Vector3 color = Vector3(0.f, 0.f, 0.f);
      for(int s = 0; s < sample; ++s)
      {
        const float u = static_cast<float>(drand48() + x) / static_cast<float>(width);
        const float v = static_cast<float>(drand48() + y) / static_cast<float>(height);
        Ray ray = camera.GenerateRay(u, v);
        color += Color(ray, scene, 0);
      }
      color /= sample;
      const int r = static_cast<int>( 255.99 * sqrt(color.r_) );
      const int g = static_cast<int>( 255.99 * sqrt(color.g_) );
      const int b = static_cast<int>( 255.99 * sqrt(color.b_) );
      std::cout << r << " " << g << " " << b << "\n";
    }
  }
}

};

int main(int argc, char *argv[])
{
  ray_tracing_weekend::Render();
  return 0;
}
