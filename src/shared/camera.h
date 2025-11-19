#pragma once

#include "vec.h"

struct Camera {
    Camera(Vec3 position);

    Vec3 position;
    Vec3 target;
};
