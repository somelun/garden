#pragma once

#include "../types.h"

struct Vec2f {
    float x, y;
};

struct Vec2i {
    u16 x, y;
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


using Point2D = Vec2i;
using Point3D = Vec3f;
