#include "matrix.h"

#include <ostream>

const Vector4 Vector4::zero  (0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::one   (1.0f, 1.0f, 1.0f, 1.0f);
const Vector4 Vector4::x_axis(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::y_axis(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::z_axis(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::w_axis(0.0f, 0.0f, 0.0f, 1.0f);

const Matrix44 Matrix44::zero(0.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 0.0f);

const Matrix44 Matrix44::identity(1.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 1.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 1.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 1.0f);

std::ostream& operator<<(std::ostream& o, const Matrix44& m)
{
    o << std::fixed;
    o << "( "<< m[0] << ", " << m[4] << ", " << m[ 8] << ", " << m[12] << " )"
      << std::endl;
    o << "( "<< m[1] << ", " << m[5] << ", " << m[ 9] << ", " << m[13] << " )"
      << std::endl;
    o << "( "<< m[2] << ", " << m[6] << ", " << m[10] << ", " << m[14] << " )"
      << std::endl;
    o << "( "<< m[3] << ", " << m[7] << ", " << m[11] << ", " << m[15] << " )";

    return o;
}

std::ostream& operator<<(std::ostream& o, const Vector4& v)
{
    o << std::fixed;
    o << "( "<< v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << " )";

    return o;
}
