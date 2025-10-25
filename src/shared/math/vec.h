#pragma once

#include "stdint.h"

struct Vec2f {
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


using Point2D = Vec2f;
