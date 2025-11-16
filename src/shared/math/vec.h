#pragma once

#include "../types.h"

struct Vec2f {
    float x, y;
};

struct Vec2i {
    i32 x, y;

    Vec2i operator+(const Vec2i& other) const {
        return {
            static_cast<i32>(x + other.x),
            static_cast<i32>(y + other.y)
        };
    }

    Vec2i operator-(const Vec2i& other) const {
        return {
            static_cast<i32>(x - other.x),
            static_cast<i32>(y - other.y)
        };
    }

    Vec2i operator*(const float& other) const {
        return {
            static_cast<i32>(x * other),
            static_cast<i32>(y * other)
        };
    }
};

struct Vec3f {
    float x, y, z;
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
using Point3D = Vec3f;
