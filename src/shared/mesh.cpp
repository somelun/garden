#include "mesh.h"
#include "loader.h"

Mesh::Mesh(const char* file_path) {
    const bool result = LoadObjFile(file_path, vertices, faces);
    if (!result) {
    
    }
}
