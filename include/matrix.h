#ifndef MATRIX_H
#define MATRIX_H

#include <iosfwd>

#if defined(__SSE4_1__)
#  include <smmintrin.h>
#elif defined(__SSSE3__)
#  include <tmmintrin.h>
#endif // __SSE4_1__ __SSSE3__

typedef float float32_t;

class Vector4
{
public: // Static constants
  static const Vector4 zero;
  static const Vector4 one;
  static const Vector4 x_axis;
  static const Vector4 y_axis;
  static const Vector4 z_axis;
  static const Vector4 w_axis;

public: // Construction, assignement, destruction
  explicit Vector4();
  explicit Vector4(float32_t s);
  explicit Vector4(float32_t x, float32_t y, float32_t z, float32_t w);
  Vector4(const Vector4& v);
  Vector4& operator=(const Vector4& v);

public: // Component access
  float32_t& operator[](std::size_t n);
  const float32_t& operator[](std::size_t n) const;

public: // Component-wise binary operations
  Vector4& operator+=(const Vector4& v);
  Vector4& operator-=(const Vector4& v);
  Vector4& operator*=(const Vector4& v);
  Vector4& operator/=(const Vector4& v);

  Vector4 operator+(const Vector4& v) const;
  Vector4 operator-(const Vector4& v) const;
  Vector4 operator*(const Vector4& v) const;
  Vector4 operator/(const Vector4& v) const;

public: // Scalar binary operations
  Vector4& operator*=(float32_t s);
  Vector4& operator/=(float32_t s);

  Vector4 operator*(float32_t s) const;
  Vector4 operator/(float32_t s) const;

public: // Component-wise unary operations
  Vector4 operator-() const;

public:
  float32_t dot(const Vector4& v) const;

public: // Comparison
  bool operator==(const Vector4& v) const;
  bool operator!=(const Vector4& v) const;

public: // Members
#if defined(__SSSE3__)
  __m128 xyzw;
} __attribute__ ((aligned (16))); // ensure 16B (SIMD) alignment
#else // !defined(__SSSE3__)
  float32_t  xyzw[4];
};
#endif // __SSSE3__

class Matrix44
{
public: // Static constants
  static const Matrix44 zero;
  static const Matrix44 identity;

public: // Construction, assignement, destruction
  Matrix44();
  Matrix44(float32_t x0, float32_t y0, float32_t z0, float32_t w0,
           float32_t x1, float32_t y1, float32_t z1, float32_t w1,
           float32_t x2, float32_t y2, float32_t z2, float32_t w2,
           float32_t x3, float32_t y3, float32_t z3, float32_t w3);
  Matrix44(const float* other);
  Matrix44(const Matrix44& other);
  Matrix44& operator=(const Matrix44& other);

public: // Component access
  float32_t& operator[](std::size_t n);
  const float32_t& operator[](std::size_t n) const;

public: // Vector binary operations
  Vector4 operator*(const Vector4& v) const;

public: // Matrix binary operations
  Matrix44 operator*(const Matrix44& m);

public: // Scalar binary operations
  Matrix44 operator+(float32_t s) const;
  Matrix44 operator-(float32_t s) const;
  Matrix44 operator*(float32_t s) const;
  Matrix44 operator/(float32_t s) const;

  Matrix44& operator+=(float32_t s);
  Matrix44& operator-=(float32_t s);
  Matrix44& operator*=(float32_t s);
  Matrix44& operator/=(float32_t s);

public: // Members
#if defined(__SSSE3__)
  __m128 components[4];
} __attribute__ ((aligned (16))); // ensure 16B (SIMD) alignment
#else // !defined(__SSSE3__)
  float32_t members[16];
};
#endif // __SSSE3__

float32_t dot(const Vector4& v1, const Vector4& v2);
Matrix44  transpose(const Matrix44& m);
Matrix44  inverse(const Matrix44& m);
Vector4*  project(Vector4* __restrict__ out, const Vector4* __restrict__ in, const Matrix44& m);

std::ostream& operator<<(std::ostream& o, const Matrix44& m);
std::ostream& operator<<(std::ostream& o, const Vector4& m);

#include "matrix.inl"

#endif // MATRIX_H

