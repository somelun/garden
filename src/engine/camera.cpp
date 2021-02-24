#include "camera.h"

const vec3f Up = {0.0f, 1.0f, 0.0f};

mat4 Camera::lookAt() {
    vec3f direction = (target_ - origin_).normalize();
    return mat4_identity();
}
