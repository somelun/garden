#pragma once

#include "vec.h"

struct Mat4 {
    float data[4][4];

    static Mat4 identity() {
        Mat4 m {};
        m.data[0][0] = m.data[1][1] = m.data[2][2] = m.data[3][3] = 1.0f;
        return m;
    }

    inline Mat4 transpose() const {
        Mat4 result;
        for (size_t r = 0; r < 4; ++r) {
            for (size_t c = 0; c < 4; ++c) {
                result.data[r][c] = data[c][r];
            }
        }
        return result;
    }
};

inline Vec4 operator*(const Vec4& v, const Mat4& m) {
    return {
        v.x * m.data[0][0] + v.y * m.data[1][0] + v.z * m.data[2][0] + v.w * m.data[3][0],
        v.x * m.data[0][1] + v.y * m.data[1][1] + v.z * m.data[2][1] + v.w * m.data[3][1],
        v.x * m.data[0][2] + v.y * m.data[1][2] + v.z * m.data[2][2] + v.w * m.data[3][2],
        v.x * m.data[0][3] + v.y * m.data[1][3] + v.z * m.data[2][3] + v.w * m.data[3][3]
    };
}

inline Vec3 operator*(const Vec3& v, const Mat4& m) {
    Vec4 r = Vec4{v.x, v.y, v.z, 1.0f} * m;
    return { r.x, r.y, r.z };
}

inline Mat4 operator*(const Mat4& a, const Mat4& b) {
    Mat4 result;
    for (size_t r = 0; r < 4; ++r) {
        for (size_t c = 0; c < 4; ++c) {
            result.data[r][c] =
                a.data[r][0] * b.data[0][c] +
                a.data[r][1] * b.data[1][c] +
                a.data[r][2] * b.data[2][c] +
                a.data[r][3] * b.data[3][c];
        }
    }
    return result;
}
