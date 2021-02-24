#pragma once

#include "math/vec.h"
#include "math/mat.h"

class Object {
public:
    Object(int n);
    ~Object();

    void addVertex(const vec3i& vertex, const int& index);
    vec3i getVertex(const int& index);
    mat4 modelMartix();

private:
    int n_;
    vec3i* vertices_;
    vec3f position_{0.0f, 0.0f, 0.0f};
    vec3f rotation_{0.0f, 0.0f, 0.0f};
};
