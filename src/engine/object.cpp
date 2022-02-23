#include "object.h"
#include "loader.h"

Object::Object(const char* filePath) {
    bool result = LoadObjFile(filePath, vertices_, triangles_);
    (void)result;
}

// Object::Object(int n) : n_(n) {
//     vertices_ = new vec3f[n_];
// }

Object::~Object() {
    // delete [] vertices_;
}

// void Object::addVertex(const vec3f& vertex, const int& index) {
//     vertices_[index] = vertex;
// }

// vec3f Object::getVertex(const int& index) {
//     return vertices_[index];
// }
