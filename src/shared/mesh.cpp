#include "mesh.h"
#include <fstream>
#include <sstream>
#include <vector>

bool Mesh::LoadFromObjFile(const char* file_path) {
    std::ifstream ifs(file_path, std::ifstream::in);
    if (!ifs.is_open()) {
        return false;
    }

    vertices.clear();
    faces.clear();
    normals.clear();
    normal_indices.clear();

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

        if (type == "vn") {
            Vec3 n;
            lss >> n.x >> n.y >> n.z;
            normals.push_back(Normalize(n));
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

                faces.push_back(--v);
                if (vn > 0) {
                    normal_indices.push_back(vn - 1);
                }
            }
        }
    }

    return true;
}
