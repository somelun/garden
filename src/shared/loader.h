#pragma once

#include "types.h"
#include "vec.h"
#include "mesh.h"

#include <fstream>
#include <sstream>
#include <vector>

static bool LoadObjFile(const char* filePath, Mesh& mesh) {
    std::ifstream ifs(filePath, std::ifstream::in);
    if (!ifs.is_open()) {
        return false;
    }

    mesh.vertices.clear();
    mesh.faces.clear();
    mesh.normals.clear();
    mesh.normal_indices.clear();

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
            mesh.vertices.push_back(v);
        }

        if (type == "vn") {
            Vec3 n;
            lss >> n.x >> n.y >> n.z;
            mesh.normals.push_back(n);
        }

        if (type == "f") {
            std::istringstream iss(line.substr(2)); // we skipping "f "
            std::string group;

            u32 v = 0, vt = 0, vn = 0;
            char slash;

            while (iss >> group) {
                // group could be "1193/1240/1193" or "1193//1193" or "1193"
                std::stringstream gss(group);

                gss >> v; // reads only the first integer before '/'

                if (gss.peek() == '/') {
                    gss >> slash;

                    if (gss.peek() != '/') {
                        gss >> vt;
                    }

                    if (gss.peek() == '/') {
                        gss >> slash;
                        gss >> vn;
                    }
                }

                mesh.faces.push_back(--v);
                if (vn > 0) {
                    mesh.normal_indices.push_back(vn - 1);
                }
            }
        }
    }

    return true;
}
