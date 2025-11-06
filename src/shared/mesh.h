#pragma once

#include "math/vec.h"
#include <vector>

class Mesh {
public:
    Mesh(const char* file_path);

private:
    std::vector<Vec3f> vertices;
    std::vector<u32> faces;
};
