#pragma once

#include "types.h"
#include "vec.h"

#include <fstream>
#include <sstream>
#include <vector>

// TODO: this requires refactoring and optimizations, made just to speedup development
static bool LoadObjFile(const char* filePath, std::vector<Vec3>& vertices, std::vector<u32>& faces) {
    std::ifstream ifs(filePath, std::ifstream::in);
    if (!ifs.is_open()) {
        return false;
    }

    vertices.clear();
    faces.clear();

    std::string line;

    while (std::getline(ifs, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream lss(line);
        std::string type;
        lss >> type;

        if (type == "v") {
            Vec3 v;
            lss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        }

        if (type == "f") {
            u16 d;
            std::istringstream iss(line.substr(2)); // we skipping "f "
            std::string group;

            while (iss >> group) {
                // group could be "1193/1240/1193" or "1193//1193" or "1193"
                std::stringstream gss(group);
                gss >> d; // reads only the first integer before '/'
                faces.push_back(--d);
            }
        }
    }

    return true;
}
