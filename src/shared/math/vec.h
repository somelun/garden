#pragma once

#include "../types.h"

struct Vec2f {
    float x, y;
};

struct Vec2i {
    i32 x, y;
};

struct Vec3f {
    float x, y, z;

    Vec3f operator-(const Vec3f& other) const {
        return { x - other.x, y - other.y, z - other.z };
    }
};

struct Vec4i {
    u8 x, y, z, w;
};

struct Vec4f {
    float x, y, z, w;
};

struct ScreenVertex {
    i32 x, y;
    float depth;
};

using Point2D = Vec2i;

inline Vec3f Cross(const Vec3f& a, const Vec3f& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
