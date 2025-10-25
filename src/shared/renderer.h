#pragma once

#include "types.h"
#include "math/vec.h"

struct Framebuffer;

class Renderer {
public:
    void SetTarget(Framebuffer* fb);

    // function used to draw scene
    // void Draw(const class Camera& camera, const std::vector<class Object>& objects);
    // void Draw(const class Camera& camera, const class Object& object);

    // functions used for direct draw to framebuffer
    void FillScreen(const Color& color);

    void DrawLine(Point2D p1, Point2D p2, const Color& color);
    // void DrawTriangle2D(const Color& color, Point p1, Point p2, Point p3);
    // void DrawQuad(const Color& color, Point p1, Point p2, Point p3, Point p4);
    // void DrawPixel(const Color& color, uint16_t x, uint16_t y);

    // used for the application class to actully draw the buffer to the screen
    // inline const Framebuffer* GetFramebuffer() const {
    //     return framebuffer_;
    // }

private:
    // void DrawTriangleBottom(const Color& color, Point p1, Point p2, Point p3);
    // void DrawTriangleTop(const Color& color, Point p1, Point p2, Point p3);

    // const vec2i ComputePixelCoordinates(const mat4& projection, const vec3f& pointWorld);

    Framebuffer* target;
};
