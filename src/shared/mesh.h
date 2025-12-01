#pragma once

#include "vec.h"
#include <vector>

class Mesh {
public:
    Mesh(const char* file_path);

    std::vector<Vec3> vertices;
    std::vector<u32> faces;

    std::vector<Vec3> normals;
    std::vector<u32> normal_indices;
};
