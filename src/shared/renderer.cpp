#include "renderer.h"

#include <utility> // std::swap
#include <cstring> // memcpy
#include <float.h> // FLT_MAX
#include "camera.h"
#include "light.h"

Renderer::~Renderer() {
    if (z_buffer) {
        delete [] z_buffer;
    }
}

void Renderer::Initialize(Framebuffer* fb) {
    target = fb;

    if (target) {
        z_buffer = new float[target->width * target->height];
    }
}

void Renderer::FillScreen(const Color8& color) {
    size_t size = target->width * target->height * 4;

    target->data[0] = PackedColor8(color);
    size_t filled = 1;

    while (filled < size) {
        size_t copy = (filled < size - filled) ? filled : (size - filled);
        memcpy(target->data + filled, target->data, copy * sizeof(u32));
        filled += copy;
    }
}

// https://haqr.eu/tinyrenderer/bresenham/
void Renderer::DrawLine(Vec2 p1, Vec2 p2, const Color8& color) {
    bool steep = std::abs(p1.x - p2.x) < std::abs(p1.y - p2.y);

    if (steep) { // if the line is steep, we transpose the image
        std::swap(p1.x, p1.y);
        std::swap(p2.x, p2.y);
    }

    if (p1.x > p2.x) { // make it left−to−right
        std::swap(p1, p2);
    }

    const u32 packed_color = PackedColor8(color);

    i32 y = p1.y;
    i32 ierror = 0;
    for (i32 x = p1.x; x <= p2.x; ++x) {
        if (steep) { // if transposed, de−transpose
            SetPixel(y, x, packed_color);
        } else {
            SetPixel(x, y, packed_color);
        }
        ierror += 2 * std::abs(p2.y - p1.y);
        y += (p2.y > p1.y ? 1 : -1) * (ierror > p2.x - p1.x);
        ierror -= 2 * (p2.x - p1.x) * (ierror > p2.x - p1.x);
    }
}

void Renderer::DrawMesh(const Mesh* mesh, const Camera camera, const Light light, RenderMode render_mode) {
    ClearZBuffer();

    Mat4 world = Mat4::Identity();

    Mat4 view = camera.GetViewMatrix();
    Mat4 projection = camera.GetProjectionMatrix();

    Mat4 mvp = world * view * projection;

    const size_t faces_num = mesh->faces.size();
    for (size_t i = 0; i < faces_num; i+=3) {
        // vertices
        Vec3 v0 = mesh->vertices[mesh->faces[i]];
        Vec3 v1 = mesh->vertices[mesh->faces[i + 1]];
        Vec3 v2 = mesh->vertices[mesh->faces[i + 2]];

        // normals
        Vec3 n0 = mesh->normals[mesh->faces[i]];
        Vec3 n1 = mesh->normals[mesh->faces[i + 1]];
        Vec3 n2 = mesh->normals[mesh->faces[i + 2]];

        if (render_mode != RenderMode::Wireframe) {
            Vec3 a = v1 - v0;
            Vec3 b = v2 - v0;
            Vec3 n = Cross(a, b);
            if (n.z >= 0) {
                continue;
            }
        }

        Vec4 p0 = v0 * mvp;
        Vec4 p1 = v1 * mvp;
        Vec4 p2 = v2 * mvp;

        if (p0.w <= 0 || p1.w <= 0 || p2.w <= 0) {
            continue;
        }

        p0.x /= p0.w;  p0.y /= p0.w;  p0.z /= p0.w;
        p1.x /= p1.w;  p1.y /= p1.w;  p1.z /= p1.w;
        p2.x /= p2.w;  p2.y /= p2.w;  p2.z /= p2.w;

        ScreenVertex s0, s1, s2;

        s0.x = (u16)((p0.x + 1.0f) * 0.5f * target->width);
        s0.y = (u16)((1.0f - p0.y) * 0.5f * target->height);
        s0.depth = p0.z;

        s1.x = (u16)((p1.x + 1.0f) * 0.5f * target->width);
        s1.y = (u16)((1.0f - p1.y) * 0.5f * target->height);
        s1.depth = p1.z;

        s2.x = (u16)((p2.x + 1.0f) * 0.5f * target->width);
        s2.y = (u16)((1.0f - p2.y) * 0.5f * target->height);
        s2.depth = p2.z;

        switch(render_mode) {
            case RenderMode::Wireframe: {
                DrawLine({s0.x, s0.y}, {s1.x, s1.y}, WHITE);
                DrawLine({s1.x, s1.y}, {s2.x, s2.y}, WHITE);
                DrawLine({s2.x, s2.y}, {s0.x, s0.y}, WHITE);
                break;
            }
            case RenderMode::Solid: {
                DrawTriangle(s0, s1, s2, WHITE);
                break;
            }
            case RenderMode::RandomColor: {
                DrawTriangle(s0, s1, s2, RandomColor8());
                break;
            }
            case RenderMode::Phong: {
                DrawTriangle(s0, s1, s2,
                             v0, v1, v2,
                             n0, n1, n2,
                             light, camera.position, WHITE);
                break;
            }
        }
    }
}

void Renderer::DrawTriangle(ScreenVertex sv1, ScreenVertex sv2, ScreenVertex sv3, const Color8& color) {
    const i32 bb_min_x = std::min(std::min(sv1.x, sv2.x), sv3.x);
    const i32 bb_min_y = std::min(std::min(sv1.y, sv2.y), sv3.y);
    const i32 bb_max_x = std::max(std::max(sv1.x, sv2.x), sv3.x);
    const i32 bb_max_y = std::max(std::max(sv1.y, sv2.y), sv3.y);

    const double total_area = TriangleAreaSigned({sv1.x, sv1.y}, {sv2.x, sv2.y}, {sv3.x, sv3.y});
    if (total_area < 1.0) {
        return;
    }

    for (i32 x = bb_min_x; x <= bb_max_x; ++x) {
        for (i32 y = bb_min_y; y<=bb_max_y; ++y) {
            double alpha = TriangleAreaSigned({x, y}, {sv2.x, sv2.y}, {sv3.x, sv3.y}) / total_area;
            double beta  = TriangleAreaSigned({x, y}, {sv3.x, sv3.y}, {sv1.x, sv1.y}) / total_area;
            double gamma = TriangleAreaSigned({x, y}, {sv1.x, sv1.y}, {sv2.x, sv2.y}) / total_area;
            if (alpha < 0 || beta < 0 || gamma < 0) {
                continue;
            }

            float depth = alpha * sv1.depth + beta  * sv2.depth + gamma * sv3.depth;
            int index = y * target->width + x;

            if (depth < z_buffer[index]) {
                z_buffer[index] = depth;
                SetPixel(x, y, PackedColor8(color));
            }
        }
    }
}

void Renderer::DrawTriangle(ScreenVertex sv1, ScreenVertex sv2, ScreenVertex sv3,
                            Vec3 w0, Vec3 w1, Vec3 w2,
                            Vec3 n0, Vec3 n1, Vec3 n2,
                            const Light& light, const Vec3& view_pos, const Color8& color) {
    const i32 bb_min_x = std::min(std::min(sv1.x, sv2.x), sv3.x);
    const i32 bb_min_y = std::min(std::min(sv1.y, sv2.y), sv3.y);
    const i32 bb_max_x = std::max(std::max(sv1.x, sv2.x), sv3.x);
    const i32 bb_max_y = std::max(std::max(sv1.y, sv2.y), sv3.y);

    const double total_area = TriangleAreaSigned({sv1.x, sv1.y}, {sv2.x, sv2.y}, {sv3.x, sv3.y});
    if (total_area == 0) return;

    for (int x = bb_min_x; x <= bb_max_x; ++x) {
        for (int y = bb_min_y; y <= bb_max_y; ++y) {
            double alpha = TriangleAreaSigned({x, y}, {sv2.x, sv2.y}, {sv3.x, sv3.y}) / total_area;
            double beta  = TriangleAreaSigned({x, y}, {sv3.x, sv3.y}, {sv1.x, sv1.y}) / total_area;
            double gamma = TriangleAreaSigned({x, y}, {sv1.x, sv1.y}, {sv2.x, sv2.y}) / total_area;

            if (alpha < 0 || beta < 0 || gamma < 0) {
                continue;
            }

            float depth = alpha * sv1.depth + beta * sv2.depth + gamma * sv3.depth;
            int index = y * target->width + x;

            if (depth < z_buffer[index]) {
                z_buffer[index] = depth;

                Vec3 world_pos = w0 * alpha + w1 * beta + w2 * gamma;

                Vec3 interpolated_normal = Normalize(
                    n0 * alpha +
                    n1 * beta +
                    n2 * gamma
                );

                ColorF lit = ComputePhong(world_pos, interpolated_normal,
                                          view_pos,
                                          light,
                                          color);

                Color8 final_color {
                    (u8)std::min(lit.r * 255.0f, 255.0f),
                    (u8)std::min(lit.g * 255.0f, 255.0f),
                    (u8)std::min(lit.b * 255.0f, 255.0f),
                    255
                };

                SetPixel(x, y, PackedColor8(final_color));
            }
        }
    }

}

void Renderer::SetPixel(const u32 x, const u32 y, const u32 packed_color) {
    const u32 index = y * target->width + x;
    target->data[index] = packed_color;
}

// variation of https://en.wikipedia.org/wiki/Shoelace_formula
double Renderer::TriangleAreaSigned(const Vec2& p1, const Vec2& p2, const Vec2& p3) {
    return 0.5 * ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
}

void Renderer::ClearZBuffer() {
    if (z_buffer && target) {
        for (u32 i = 0; i < target->width * target->height; ++i) {
            z_buffer[i] = FLT_MAX;
        }
    }
}
