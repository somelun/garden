#include "mesh.h"
#include "loader.h"

Mesh::Mesh(const char* file_path) {
    const bool result = LoadObjFile(file_path, vertices, triangles);
    if (!result) {
        // maybe I need to print an error
    }
}
