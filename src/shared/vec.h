#pragma once

#include "types.h"
#include <cmath>

struct Vec2 {
    i32 x, y;
};

struct Vec3 {
    float x, y, z;

    Vec3 operator+(const Vec3& other) const {
        return { x + other.x, y + other.y, z + other.z };
    }

    Vec3 operator-(const Vec3& other) const {
        return { x - other.x, y - other.y, z - other.z };
    }

    Vec3 operator*(const float f) const {
        return { x * f, y * f, z * f };
    }
};

inline Vec3 Normalize(const Vec3& v) {
    float len_sq = v.x * v.x + v.y * v.y + v.z * v.z;

    if (len_sq < 1e-8f) {
        return {0,0,0};
    }

    float inv = 1.0f / std::sqrtf(len_sq);
    return { v.x * inv, v.y * inv, v.z * inv };
}

inline float Dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vec3 Cross(const Vec3& a, const Vec3& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

struct Vec4 {
    float x, y, z, w;
};

struct ScreenVertex {
    i32 x, y;
    float depth;
};
