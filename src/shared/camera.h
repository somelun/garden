#pragma once

#include "math/vec.h"

struct Camera {
    Camera(Vec3f position);

    Vec3f position;
    Vec3f target;
};
