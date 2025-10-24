#pragma once

#include "math/vec.h"
#include <fstream>
#include <sstream>
#include <vector>

// TODO: this requires refactoring and optimizations, made just to speedup development
// [[maybe_unused]]
static bool LoadObjFile(const char* filePath, std::vector<Vec3f>& vertices, std::vector<uint16_t>& triangles) {
    std::ifstream ifs(filePath, std::ifstream::in);
    if (!ifs.is_open()) {
        return false;
    }

    vertices.clear();
    triangles.clear();

    std::string line;

    while (std::getline(ifs, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v") {
            Vec3f v;
            ss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        }

        if (type == "f") {
            uint16_t d;
            for (size_t i = 0; i < 3; ++i) {
                ss >> d;
                triangles.push_back(--d); // because in .obj file index starts from 1
            }
        }
    }

    return true;
}
