#include "camera.h"

Camera::Camera() {
    // TODO: remove this hardcod
    projection = mat4_perspective(90.0f, 0.1f, 100.0f);
}
