#pragma once

#include "types.h"
#include "vec.h"
#include "mesh.h"

struct Camera;
struct Light;
struct Framebuffer;

enum class RenderMode : u8 {
    Wireframe,
    Solid,
    RandomColor,
    Phong
};

class Renderer {
public:
    ~Renderer();
    void Initialize(Framebuffer* fb);

    void FillScreen(const Color8& color);

    void DrawMesh(const Mesh* mesh, const Camera camera, const Light light, RenderMode render_mode = RenderMode::Wireframe);

private:
    void SetPixel(const u32 x, const u32 y, const u32 packed_color);
    void DrawLine(Vec2 p1, Vec2 p2, const Color8& color);
    void DrawTriangle(ScreenVertex sv1, ScreenVertex sv2, ScreenVertex sv3, const Color8& color);
    void DrawTriangle(ScreenVertex sv1, ScreenVertex sv2, ScreenVertex sv3,
                      Vec3 w0, Vec3 w1, Vec3 w2,
                      Vec3 n0, Vec3 n1, Vec3 n2,
                      const Light& light, const Vec3& view_pos, const Color8& color);

    double TriangleAreaSigned(const Vec2& p1, const Vec2& p2, const Vec2& p3);
    void ClearZBuffer();

    Framebuffer* target;
    float* z_buffer;
};
