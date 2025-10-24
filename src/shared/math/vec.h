#pragma once

#include "stdint.h"

struct Vec2 {
    float x, y;
};

struct Vec3f {
    float x, y, z;
};

struct Vec4i {
    uint8_t x, y, z, w;
};

struct Vec4f {
    float x, y, z, w;
};

using Color = Vec4i;
using Point = Vec3f;
