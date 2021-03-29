#pragma once

#include "math/vec.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include "math/mat.h"

class Framebuffer;

class Renderer {
public:
    Renderer(uint16_t width, uint16_t height);
    ~Renderer();

    void Present();

    vec2f Project(vec3f coord, mat4 trans);
    void Render(const class Camera& camera, const std::vector<class Object>& objects);

    inline Framebuffer* GetFramebuffer() {
        return framebuffer_;
    }

    // direct access to framebuffer
    void DrawTriangle2D(const Color& color, Point p1, Point p2, Point p3);
    void DrawQuad(const Color& color, Point p1, Point p2, Point p3, Point p4);
    void DrawLine(const Color& color, int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    void DrawPixel(const Color& color, uint16_t x, uint16_t y);

    void FillScreen(const Color& color);

private:
    void DrawTriangleBottom(const Color& color, Point p1, Point p2, Point p3);
    void DrawTriangleTop(const Color& color, Point p1, Point p2, Point p3);

    class Framebuffer* framebuffer_;
};
