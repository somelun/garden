#pragma once

#include "../math/mat.h"

class Renderer;

class TestScene {
public:
    TestScene(Renderer& renderer);

    void update(double dt);

private:
    Renderer& renderer_;
    
    void computePixelCoordinates(
        const vec3f pWorld,
        vec2i &pRaster,
        const mat4 &worldToCamera,
        const float &canvasWidth,
        const float &canvasHeight,
        const uint32_t &imageWidth,
        const uint32_t &imageHeight
    );
};
