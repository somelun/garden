#pragma once

#include "types.h"

struct Vec2 {
    i32 x, y;
};

struct Vec3 {
    float x, y, z;

    Vec3 operator-(const Vec3& other) const {
        return { x - other.x, y - other.y, z - other.z };
    }
};

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
