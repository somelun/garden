#pragma once

#include "types.h"
#include "math/vec.h"
#include "mesh.h"

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
    void DrawMesh(const Mesh* mesh);
    // void DrawTriangle2D(const Color& color, Point p1, Point p2, Point p3);
    // void DrawQuad(const Color& color, Point p1, Point p2, Point p3, Point p4);

private:
    void SetPixel(const u32 x, const u32 y, const u32 packed_color);
    void ProjectToScreen();

    // void DrawTriangleBottom(const Color& color, Point p1, Point p2, Point p3);
    // void DrawTriangleTop(const Color& color, Point p1, Point p2, Point p3);

    // const vec2i ComputePixelCoordinates(const mat4& projection, const vec3f& pointWorld);

    Framebuffer* target;
};
