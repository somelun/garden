#pragma once

#include <iostream>
#include "vec.h"

using mat_t = float;

constexpr float kPI = 3.14159265359f;
constexpr float kPI180 = kPI / 180.0f;
constexpr float k180PI = 180.0f / kPI;

#define degreesToRadians(x) (x * kPI180)
#define radiansToDegrees(x) (x * k180PI)

class mat4 {
public:
    
    mat4() {};
    mat4(mat_t a00, mat_t a01, mat_t a02, mat_t a03,
         mat_t a10, mat_t a11, mat_t a12, mat_t a13,
         mat_t a20, mat_t a21, mat_t a22, mat_t a23,
         mat_t a30, mat_t a31, mat_t a32, mat_t a33);

    mat_t& at(int row, int column);
    const mat_t& at(int row, int column) const;
    
    mat4 operator*(const mat4& m) const;
    vec4f operator*(const vec4f& v) const;

    mat4 transpose();
    mat4 inverse();
    
    friend std::ostream& operator<<(std::ostream& s, const mat4& m);

private:
    mat4 adjoint();
    mat_t cofactor(size_t r, size_t c);
    mat_t minor(size_t r, size_t c);
    
    mat_t data_[16] = {0};
};

[[maybe_unused]]
static mat4 mat4_identity() {
    mat4 m;
    m.at(0, 0) = m.at(1, 1) = m.at(2, 2) = m.at(3, 3) = 1.0f;
    return m;
}

[[maybe_unused]]
static mat4 mat_translate(const vec3f& v) {
    mat4 m = mat4_identity();
    m.at(0, 3) = v.x;
    m.at(1, 3) = v.y;
    m.at(2, 3) = v.z;
    return m;
}

[[maybe_unused]]
static mat4 mat4_scale(const vec3f& v) {
    mat4 m;
    m.at(0, 0) = v.x;
    m.at(1, 1) = v.y;
    m.at(2, 2) = v.z;
    m.at(3, 3) = 1.0f;
    return m;
}

[[maybe_unused]]
static mat4 mat4_rotate_x(const float degrees) {
    mat4 m;
    const float radians = degreesToRadians(degrees);

    m.at(1, 1) = cosf(radians);
    m.at(1, 2) = sinf(radians);
    m.at(2, 1) = -m.at(1, 2);
    m.at(2, 2) = m.at(1, 1);

    return m;
}

[[maybe_unused]]
static mat4 mat4_rotate_y(const float degrees) {
    mat4 m;
    const float radians = degreesToRadians(degrees);

    m.at(0, 0) = cosf(radians);
    m.at(2, 0) = sinf(radians);
    m.at(0, 2) = -m.at(0, 0);
    m.at(2, 2) = m.at(0, 0);

    return m;
}

[[maybe_unused]]
static mat4 mat4_rotate_z(const float degrees) {
    mat4 m;
    const float radians = degreesToRadians(degrees);

    m.at(0, 0) = cosf(radians);
    m.at(1, 0) = sinf(radians);
    m.at(0, 1) = -m.at(1, 0);
    m.at(1, 1) = m.at(0, 0);

    return m;
}

// [[maybe_unused]]
// static mat4 mat4_rotate(const vec3f& v) {
//     mat4 m;
//     return m;
// }

[[maybe_unused]]
static mat4 mat_test() {
    mat4 m;
    int t = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m.at(i, j) = ++t;
        }
    }
    return m;
}

class mat3 {
public:
    friend std::ostream& operator<<(std::ostream& s, const mat3& m);
    
private:
    friend class mat4;
    
    mat_t determinant();
    
    mat_t data_[9] = {0};
};
