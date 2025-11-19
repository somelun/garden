#pragma once

#include "vec.h"
#include <vector>

class Mesh {
public:
    Mesh(const char* file_path);

// private:
    std::vector<Vec3> vertices;
    std::vector<u32> faces;
};
