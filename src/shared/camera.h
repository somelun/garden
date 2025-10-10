#pragma once

#include "math/vec.h"
#include "math/mat.h"

// enum class ProjectionType {
//     Perspective = 0,
//     Orthographic,
// };

// http://www.songho.ca/opengl/gl_camera.html
class Camera {
public:
    Camera();

    mat4 projection;
private:
    // ProjectionType projectionType_{ProjectionType::Perspective};
};
