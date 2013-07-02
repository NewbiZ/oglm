#ifndef MATRIX_INL
#define MATRIX_INL

//==============================================================================
// Vector4
//==============================================================================
inline
Vector4::Vector4()
{
}

inline
Vector4::Vector4(float32_t s)
{
#if defined(__SSSE3__)
  xyzw = _mm_set1_ps(s);
#else // !defined(__SSSE3__)
  xyzw[0] = s;
  xyzw[1] = s;
  xyzw[2] = s;
  xyzw[3] = s;
#endif // __SSSE3__
}

inline
Vector4::Vector4(float32_t x, float32_t y, float32_t z, float32_t w)
{
#if defined(__SSSE3__)
  xyzw = _mm_set_ps(w, z, y, x);
#else // !defined(__SSSE3__)
  xyzw[0] = x;
  xyzw[1] = y;
  xyzw[2] = z;
  xyzw[3] = w;
#endif // __SSSE3__
}

inline
Vector4::Vector4(const Vector4& v)
#if defined(__SSSE3__)
  : xyzw(v.xyzw)
{
}
#else // !defined(__SSSE3__)
{
  xyzw[0] = v.xyzw[0];
  xyzw[1] = v.xyzw[1];
  xyzw[2] = v.xyzw[2];
  xyzw[3] = v.xyzw[3];
}
#endif // __SSSE3__

inline
Vector4& Vector4::operator=(const Vector4& v)
{
  if (this!=&v)
  {
#if defined(__SSSE3__)
    xyzw = v.xyzw;
#else // !defined(__SSSE3__)
    xyzw[0] = v.xyzw[0];
    xyzw[1] = v.xyzw[1];
    xyzw[2] = v.xyzw[2];
    xyzw[3] = v.xyzw[3];
#endif // __SSSE3__
  }

  return *this;
}

inline
float32_t& Vector4::operator[](std::size_t n)
{
  return ((float32_t*)&xyzw)[n];
}

inline
const float32_t& Vector4::operator[](std::size_t n) const
{
  return ((float32_t*)&xyzw)[n];
}

inline
Vector4& Vector4::operator+=(const Vector4& v)
{
#if defined(__SSSE3__)
  xyzw = _mm_add_ps(xyzw, v.xyzw);
#else // !defined(__SSSE3__)
  xyzw[0] += v.xyzw[0];
  xyzw[1] += v.xyzw[1];
  xyzw[2] += v.xyzw[2];
  xyzw[3] += v.xyzw[3];
#endif // __SSSE3__
  return *this;
}

inline
Vector4& Vector4::operator-=(const Vector4& v)
{
#if defined(__SSSE3__)
  xyzw = _mm_sub_ps(xyzw, v.xyzw);
#else // !defined(__SSSE3__)
  xyzw[0] -= v.xyzw[0];
  xyzw[1] -= v.xyzw[1];
  xyzw[2] -= v.xyzw[2];
  xyzw[3] -= v.xyzw[3];
#endif // __SSSE3__
  return *this;
}

inline
Vector4& Vector4::operator*=(const Vector4& v)
{
#if defined(__SSSE3__)
  xyzw = _mm_mul_ps(xyzw, v.xyzw);
#else // !defined(__SSSE3__)
  xyzw[0] *= v.xyzw[0];
  xyzw[1] *= v.xyzw[1];
  xyzw[2] *= v.xyzw[2];
  xyzw[3] *= v.xyzw[3];
#endif // __SSSE3__
  return *this;
}

inline
Vector4& Vector4::operator/=(const Vector4& v)
{
#if defined(__SSSE3__)
  xyzw = _mm_div_ps(xyzw, v.xyzw);
#else // !defined(__SSSE3__)
  xyzw[0] /= v.xyzw[0];
  xyzw[1] /= v.xyzw[1];
  xyzw[2] /= v.xyzw[2];
  xyzw[3] /= v.xyzw[3];
#endif // __SSSE3__
  return *this;
}

inline
Vector4& Vector4::operator*=(float32_t s)
{
#if defined(__SSSE3__)
  xyzw = _mm_mul_ps(xyzw, _mm_set1_ps(s));
#else // !defined(__SSSE3__)
  xyzw[0] *= s;
  xyzw[1] *= s;
  xyzw[2] *= s;
  xyzw[3] *= s;
#endif // __SSSE3__
  return *this;
}

inline
Vector4& Vector4::operator/=(float32_t s)
{
#if defined(__SSSE3__)
  xyzw = _mm_div_ps(xyzw, _mm_set1_ps(s));
#else // !defined(__SSSE3__)
  xyzw[0] /= s;
  xyzw[1] /= s;
  xyzw[2] /= s;
  xyzw[3] /= s;
#endif // __SSSE3__
  return *this;
}

inline
Vector4 Vector4::operator+(const Vector4& v) const
{
  Vector4 result(*this);
  result += v;
  return result;
}

inline
Vector4 Vector4::operator-(const Vector4& v) const
{
  Vector4 result(*this);
  result -= v;
  return result;
}

inline
Vector4 Vector4::operator*(const Vector4& v) const
{
  Vector4 result(*this);
  result *= v;
  return result;
}

inline
Vector4 Vector4::operator/(const Vector4& v) const
{
  Vector4 result(*this);
  result /= v;
  return result;
}

inline
Vector4 Vector4::operator*(float32_t s) const
{
  Vector4 result(*this);
  result *= s;
  return result;
}

inline
Vector4 Vector4::operator/(float32_t s) const
{
  Vector4 result(*this);
  result /= s;
  return result;
}

inline
Vector4 Vector4::operator-() const
{
  Vector4 result;
#if defined(__SSSE3__)
  static const __m128 signmask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
  result.xyzw = _mm_xor_ps(signmask, xyzw);
#else // !defined(__SSSE3__)
  result.xyzw[0] = -xyzw[0];
  result.xyzw[1] = -xyzw[1];
  result.xyzw[2] = -xyzw[2];
  result.xyzw[3] = -xyzw[3];
#endif // __SSSE3__
  return result;
}

inline
bool Vector4::operator==(const Vector4& v) const
{
#if defined(__SSSE3__)
  return _mm_movemask_ps(_mm_cmpneq_ps(xyzw, v.xyzw))==0;
#else // !defined(__SSSE3__)
  return xyzw[0] == v.xyzw[0] &&
         xyzw[1] == v.xyzw[1] &&
         xyzw[2] == v.xyzw[2] &&
         xyzw[3] == v.xyzw[3];
#endif // __SSSE3__
}

inline
bool Vector4::operator!=(const Vector4& v) const
{
#if defined(__SSSE3__)
  return _mm_movemask_ps(_mm_cmpeq_ps(xyzw, v.xyzw))==0;
#else // !defined(__SSSE3__)
  return xyzw[0] != v.xyzw[0] ||
         xyzw[1] != v.xyzw[1] ||
         xyzw[2] != v.xyzw[2] ||
         xyzw[3] != v.xyzw[3];
#endif // __SSSE3__
}

inline
float32_t Vector4::dot(const Vector4& v) const
{
  float32_t result;
#if defined(__SSE4_1__)
  __m128 dp = _mm_dp_ps(xyzw, v.xyzw, 0xF1);
  _mm_store_ss(&result, dp);
#elif defined(__SSSE3__)
  __m128 m = _mm_mul_ps(xyzw, v.xyzw);
  __m128 a1 = _mm_hadd_ps(m, m);
  __m128 a2 = _mm_hadd_ps(a1, a1);
  _mm_store_ss(&result, a2);
#else // !defined(__SSE4_1__) && !defined(__SSSE3__)
  result  = xyzw[0] * v.xyzw[0];
  result += xyzw[1] * v.xyzw[1];
  result += xyzw[2] * v.xyzw[2];
  result += xyzw[3] * v.xyzw[3];
#endif // __SSSE3__ __SSE4_1__
  return result;
}

//==============================================================================
// Matrix44
//==============================================================================
inline
Matrix44::Matrix44()
{
}

inline
Matrix44::Matrix44(float32_t x0, float32_t y0, float32_t z0, float32_t w0,
                   float32_t x1, float32_t y1, float32_t z1, float32_t w1,
                   float32_t x2, float32_t y2, float32_t z2, float32_t w2,
                   float32_t x3, float32_t y3, float32_t z3, float32_t w3)
{
#if defined(__SSSE3__)
  components[0] = _mm_set_ps(w0, z0, y0, x0);
  components[1] = _mm_set_ps(w1, z1, y1, x1);
  components[2] = _mm_set_ps(w2, z2, y2, x2);
  components[3] = _mm_set_ps(w3, z3, y3, x3);
#else // !defined(__SSSE3__)
  components[ 0] = x0;
  components[ 1] = y0;
  components[ 2] = z0;
  components[ 3] = w0;
  components[ 4] = x1;
  components[ 5] = y1;
  components[ 6] = z1;
  components[ 7] = w1;
  components[ 8] = x2;
  components[ 9] = y2;
  components[10] = z2;
  components[11] = w2;
  components[12] = x3;
  components[13] = y3;
  components[14] = z3;
  components[15] = w3;
#endif // __SSSE3__
}

inline
Matrix44::Matrix44(const Matrix44& other)
{
#if defined(__SSSE3__)
  components[0] = other.components[0];
  components[1] = other.components[1];
  components[2] = other.components[2];
  components[3] = other.components[3];
#else // !defined(__SSSE3__)
  std::memcpy(members, other.members, sizeof(members));
#endif // __SSSE3__
}

inline
float32_t& Matrix44::operator[](std::size_t n)
{
  return ((float32_t*)&components)[n];
}

inline
const float32_t& Matrix44::operator[](std::size_t n) const
{
  return ((const float32_t*)&components)[n];
}

//==============================================================================
// ALGEBRA
//==============================================================================
inline
float32_t dot(const Vector4& lhs, const Vector4& rhs)
{
  float32_t result;
#if defined(__SSE4_1__)
  __m128 dp = _mm_dp_ps(lhs.xyzw, rhs.xyzw, 0xF1);
  _mm_store_ss(&result, dp);
#elif defined(__SSSE3__)
  __m128 m = _mm_mul_ps(lhs.xyzw, rhs.xyzw);
  __m128 a1 = _mm_hadd_ps(m, m);
  __m128 a2 = _mm_hadd_ps(a1, a1);
  _mm_store_ss(&result, a2);
#else // !defined(__SSE4_1__) && !defined(__SSSE3__)
  result  = lhs.xyzw[0] * rhs.xyzw[0];
  result += lhs.xyzw[1] * rhs.xyzw[1];
  result += lhs.xyzw[2] * rhs.xyzw[2];
  result += lhs.xyzw[3] * rhs.xyzw[3];
#endif // __SSSE3__ __SSE4_1__
  return result;
}

inline
Matrix44 transpose(const Matrix44& m)
{
  //TODO
  return Matrix44::zero;
}

inline
Matrix44 inverse(const Matrix44& m)
{
  //TODO
  return Matrix44::zero;
}

inline
Vector4* project(Vector4* __restrict__ out, const Vector4* __restrict__ in, const Matrix44& m)
{
  //TODO
  return 0;
}

#endif // MATRIX_INL

