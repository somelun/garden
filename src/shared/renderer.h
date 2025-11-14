#pragma once

#include "types.h"
#include "math/vec.h"
#include "mesh.h"

struct Framebuffer;

class Renderer {
public:
    void SetTarget(Framebuffer* fb);

    void FillScreen(const Color& color);

    void DrawLine(Point2D p1, Point2D p2, const Color& color);
    void DrawMesh(const Mesh* mesh);
    void DrawTriangle(Point2D p1, Point2D p2, Point2D p3, const Color& color);

private:
    Point2D ProjectToScreen(Point3D vertex);
    void SetPixel(const u32 x, const u32 y, const u32 packed_color);

    double TriangleAreaSigned(Point2D p1, Point2D p2, Point2D p3);

    Framebuffer* target;
};
