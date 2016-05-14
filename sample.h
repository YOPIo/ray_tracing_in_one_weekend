#ifndef SAMPLE_H
#define SAMPLE_H

#include <random>

#include "vector.h"

namespace ray_tracing_weekend
{

class Sample
{
 public:
  static Vector3 UnitSphere()
  {
    Vector3 p = Vector3(0.f, 0.f, 0.f);
    do
    {
      p = 2.f * Vector3(drand48(), drand48(), drand48()) - Vector3(1.f, 1.f, 1.f);
    }while( p.LengthSquared() >= 1.f );
    return p;
  }

  static Vector3 UnitCircle()
  {
    Vector3 p = Vector3(0.f, 0.f, 0.f);
    do
    {
      p = 2.f * Vector3(drand48(), drand48(), drand48()) - Vector3(1.f, 1.f, 1.f);
    }while( Dot(p, p) >= 1.f );
    return p;
  }

};

};

#endif // SAMPLE_H
