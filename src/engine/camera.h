#pragma once

#include "math/vec.h"
#include "math/mat.h"

class Camera {
public:
    Camera(vec3f origin, vec3f target) : origin_(origin), target_(target) {};

    mat4 lookAt();
private:
    vec3f origin_;
    vec3f target_;
};
