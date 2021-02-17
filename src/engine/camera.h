#pragma once

#include "math/vec.h"

class Camera {
public:
    Camera(vec3f origin, vec3f lookAt) : origin_(origin), lookAt_(lookAt) {};
private:
    vec3f origin_;
    vec3f lookAt_;
};
