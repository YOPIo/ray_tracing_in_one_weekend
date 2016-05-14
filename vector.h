#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>
#include <cmath>

namespace ray_tracing_weekend
{

struct Vector3
{
  Vector3() {}

  Vector3(const float x,
          const float y,
          const float z) :
    x_(x),
    y_(y),
    z_(z)
  {}

  Vector3(const Vector3& v) :
    x_(v.x_),
    y_(v.y_),
    z_(v.z_)
  {}

  Vector3(const float v) :
    x_(v),
    y_(v),
    z_(v)
  {}

  ~Vector3() {}

  Vector3 operator = (const Vector3& v)
  {
    this->x_ = v.x_;
    this->y_ = v.y_;
    this->z_ = v.z_;
    return *this;
  }

  float operator [] (const size_t index)
  {
    assert(0 <= index && index < 3);
    return (&x_)[index];
  }

  inline float LengthSquared() const
  {
    return x_ * x_ + y_ * y_ + z_ * z_;
  }

  inline float Length() const
  {
    return sqrt( LengthSquared() );
  }

  inline void Normalize()
  {
    float inv_length = 1.f / Length();
    this->x_ *= inv_length;
    this->y_ *= inv_length;
    this->z_ *= inv_length;
  }

  union
  {
    struct { float x_, y_, z_; };
    struct { float r_, g_, b_; };
  };
}; // Vector3

/* ---------- Vector3 演算子オーバーライド ---------- */

inline Vector3 operator + (const Vector3& u, const Vector3& v)
{
  return Vector3(u.x_ + v.x_, u.y_ + v.y_, u.z_ + v.z_);
}

inline Vector3 operator += (Vector3& u, const Vector3& v)
{
  u.x_ += v.x_;
  u.y_ += v.y_;
  u.z_ += v.z_;
  return u;
}

inline Vector3 operator - (const Vector3& v)
{
  return Vector3(-v.x_, -v.y_, -v.z_);
}

inline Vector3 operator - (const Vector3& u, const Vector3& v)
{
  return Vector3(u.x_ - v.x_, u.y_ - v.y_, u.z_ - v.z_);
}

inline Vector3 operator -= (Vector3& u, const Vector3& v)
{
  u.x_ -= v.x_;
  u.y_ -= v.y_;
  u.z_ -= v.z_;
  return u;
}

inline Vector3 operator * (const Vector3& u, const Vector3& v)
{
  return Vector3(u.x_ * v.x_, u.y_ * v.y_, u.z_ * v.z_);
}

inline Vector3 operator *= (Vector3& u, const Vector3& v)
{
  u.x_ *= v.x_;
  u.y_ *= v.y_;
  u.z_ *= v.z_;
  return u;
}

inline Vector3 operator * (const Vector3& u, const float v)
{
  return Vector3(u.x_ * v, u.y_ * v, u.z_ * v);
}

inline Vector3 operator * (const float u, const Vector3& v)
{
  return Vector3(u * v.x_, u * v.y_, u * v.z_);
}

inline Vector3 operator *= (Vector3& u, const float v)
{
  u.x_ *= v;
  u.y_ *= v;
  u.z_ *= v;
  return u;
}

inline Vector3 operator / (const Vector3& u, const float v)
{
  return Vector3(u.x_ / v, u.y_ / v, u.z_ / v);
}

inline Vector3 operator /= (Vector3& u, const float v)
{
  u.x_ /= v;
  u.y_ /= v;
  u.z_ /= v;
  return u;
}

inline bool operator == (const Vector3& u, const Vector3& v)
{
  return (u.x_ == v.x_ && u.y_ == v.y_ && u.z_ == v.z_);
}

inline bool operator != (const Vector3& u, const Vector3& v)
{
  return (u.x_ != v.x_ || u.y_ != v.y_ || u.z_ != v.z_);
}

inline float Dot(const Vector3& u, const Vector3& v)
{
  return u.x_ * v.x_ + u.y_ * v.y_ + u.z_ * v.z_;
}

inline Vector3 Cross(const Vector3& u, const Vector3& v)
{
  return Vector3( (u.y_ * v.z_) - (u.z_ * v.y_),
                  (u.z_ * v.x_) - (u.x_ * v.z_),
                  (u.x_ * v.y_) - (u.y_ * v.x_) );
}

inline Vector3 Normalize(const Vector3& v)
{
  return v / v.Length();
}

} // ray_tracing_weekend

#endif // VECTOR_H
