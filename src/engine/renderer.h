#pragma once

#include "maths.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>

class Framebuffer;

class Renderer {
public:
    Renderer(uint16_t width, uint16_t height);
    ~Renderer();

    void Present();

    inline Framebuffer* GetFramebuffer() {
        return framebuffer_;
    }

    void DrawTriangle2D(const Color& color, Point p1, Point p2, Point p3);

    void DrawQuad(const Color& color, Point p1, Point p2, Point p3, Point p4);

    void DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, const Color& color);
    void DrawPixel(uint16_t x, uint16_t y, const Color& color);

    void FillScreen(const Color& color);

private:
    void DrawTriangleBottom(const Color& color, Point p1, Point p2, Point p3);
    void DrawTriangleTop(const Color& color, Point p1, Point p2, Point p3);

    class Framebuffer* framebuffer_;
};
