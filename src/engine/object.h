#pragma once

#include "math/vec.h"
#include "math/mat.h"

class Object {
public:
    Object(int n);
    ~Object();

    void addVertex(const vec3f& vertex, const int& index);
    vec3f getVertex(const int& index);
    mat4 modelMartix();

private:
    int n_;
    vec3f* vertices_;
    vec3f position_{0.0f, 0.0f, 0.0f};
    vec3f rotation_{0.0f, 0.0f, 0.0f};
};
// TODO:so, lets think that we keep scale, rotation and transform here, inside the object
// then renderer can just access it in its loop and create all matices and then apply
// those transformations to the object during its rendering. is that good approach?
