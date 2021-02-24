#include "object.h"

Object::Object(int n) : n_(n) {
    vertices_ = new vec3i[n_];
}

Object::~Object() {
    delete [] vertices_;
}

void Object::addVertex(const vec3i& vertex, const int& index) {
    vertices_[index] = vertex;
}

vec3i Object::getVertex(const int& index) {
    return vertices_[index];
}
