#pragma once

#include "types.h"
#include "math/vec.h"
#include "mesh.h"

struct Framebuffer;

class Renderer {
public:
    ~Renderer();
    void SetTarget(Framebuffer* fb);

    void FillScreen(const Color& color);

    void DrawLine(Point2D p1, Point2D p2, const Color& color);
    void DrawMesh(const Mesh* mesh);
    void DrawTriangle(ScreenVertex sv1, ScreenVertex sv2, ScreenVertex sv3, const Color& color);

private:
    ScreenVertex ProjectToScreen(Point3D vertex);
    void SetPixel(const u32 x, const u32 y, const u32 packed_color);

    double TriangleAreaSigned(const Point2D& p1, const Point2D& p2, const Point2D& p3);

    void ClearZBuffer();

    Framebuffer* target;
    float* z_buffer;
};
