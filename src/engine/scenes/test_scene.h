#pragma once

#include "../math/mat.h"

class Renderer;

class TestScene {
public:
    TestScene(Renderer& renderer);
    ~TestScene();

    void Update(double dt);

private:
    Renderer& renderer_;
    class Object* object_;
    class Camera* camera_;
};
