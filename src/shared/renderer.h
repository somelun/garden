#pragma once

#include "types.h"
#include "vec.h"
#include "mesh.h"

struct Camera;
struct Framebuffer;

enum class RenderMode : u8 {
    Wireframe,
    Solid,
    RandomColor
};

class Renderer {
public:
    ~Renderer();
    void Initialize(Framebuffer* fb);

    void FillScreen(const Color& color);

    void DrawLine(Vec2 p1, Vec2 p2, const Color& color);
    void DrawMesh(const Mesh* mesh, const Camera* camera, RenderMode render_mode = RenderMode::Wireframe);
    void DrawTriangle(ScreenVertex sv1, ScreenVertex sv2, ScreenVertex sv3, const Color& color);

private:
    void SetPixel(const u32 x, const u32 y, const u32 packed_color);

    double TriangleAreaSigned(const Vec2& p1, const Vec2& p2, const Vec2& p3);

    void ClearZBuffer();

    Framebuffer* target;
    float* z_buffer;
};
