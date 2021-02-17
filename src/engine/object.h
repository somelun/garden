#pragma once

#include "math/vec.h"

class Object {
public:
    Object(int n);
    ~Object();

    void addVertex(const vec3i& vertex, const int& index);

private:
    int n_;
    vec3i* vertices_;
    vec3f position_{0.0f, 0.0f, 0.0f};
    vec3f rotation_{0.0f, 0.0f, 0.0f};
};
