#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "matrix.h"

int main(int argc, char** argv)
{
#if defined(__SSE4_1__)
  std::cout << "SSE4.1 enabled" << std::endl;
#elif defined(__SSSE3__)
  std::cout << "SSSE3 enabled" << std::endl;
#else // !defined(__SSSE3__) && !defined(__SSE4_1__)
  std::cout << "SIMD disabled" << std::endl;
#endif // __SSSE3__ __SSE4_1__

  // Addition
  {
    Vector4 computed(Vector4::x_axis + Vector4::y_axis + Vector4::z_axis);
    Vector4 expected(1.0f, 1.0f, 1.0f, 0.0f);
    assert(computed == expected);
  }

  // Substraction
  {
    Vector4 computed(Vector4::one - (Vector4::x_axis + Vector4::y_axis + Vector4::z_axis));
    Vector4 expected(0.0f, 0.0f, 0.0f, 1.0f);
    assert(computed == expected);
  }

  // Scalar multiplication
  {
    Vector4 computed(Vector4::one * 5.0f);
    Vector4 expected(5.0f, 5.0f, 5.0f, 5.0f);
    assert(computed == expected);
  }

  // Negation multiplication
  {
    Vector4 computed(-(Vector4::one * -1.0f));
    Vector4 expected(-Vector4::one * -1.0f);
    assert(computed == expected);
  }

  // Arithmetic test
  {
    Vector4 v(Vector4::one);
    v *= 2.0f;
    v = v / 2.0f;
    v += Vector4::one;
    v = v - Vector4::one;
    v[0] = 0.0f;
    v[1] = 1.0f;
    v[2] = 2.0f;
    v[3] = 3.0f;
    Vector4 v2(1.0f, 0.0f, -1.0f, -2.0f);
    v += v2;
    assert(v==Vector4::one);
  }

  // Dot product
  {
    Vector4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector4 v2(2.0f, 3.0f, 4.0f, 5.0f);
    float32_t computed = v1.dot(v2);
    float32_t expected = 40.0f;
    assert(v1.dot(v2) == expected);
  }

  // Structure sizes
  {
    assert(sizeof(Vector4) == sizeof(float32_t)*4);
    assert(sizeof(Matrix44) == sizeof(float32_t)*4*4);
  }

  // Matrix/vector projection
  {
    std::vector<Vector4> vertices;
    vertices.push_back(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
    vertices.push_back(Vector4(1.0f, 1.0f, 0.0f, 1.0f));
    vertices.push_back(Vector4(1.0f, 0.0f, 1.0f, 1.0f));
    vertices.push_back(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    vertices.push_back(Vector4(1.0f, 2.0f, 3.0f, 1.0f));

    Matrix44 m1 = Matrix44::identity;
    Matrix44 m2 = Matrix44::zero;
    Matrix44 m3(4.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 2.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f);

    std::cout << m1 << std::endl;
    std::cout << std::endl;
    std::cout << m2 << std::endl;
    std::cout << std::endl;
    std::cout << m3 << std::endl;
  }

  return EXIT_SUCCESS;
}

