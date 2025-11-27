#include "renderer.h"

#include <utility> // std::swap
#include <cstring> // memcpy
#include <float.h> // FLT_MAX

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

void Renderer::FillScreen(const Color& color) {
    size_t size = target->width * target->height * 4;

    target->data[0] = PackedColor(color);
    size_t filled = 1;

    while (filled < size) {
        size_t copy = (filled < size - filled) ? filled : (size - filled);
        memcpy(target->data + filled, target->data, copy * sizeof(u32));
        filled += copy;
    }
}

// https://haqr.eu/tinyrenderer/bresenham/
void Renderer::DrawLine(Vec2 p1, Vec2 p2, const Color& color) {
    bool steep = std::abs(p1.x - p2.x) < std::abs(p1.y - p2.y);

    if (steep) { // if the line is steep, we transpose the image
        std::swap(p1.x, p1.y);
        std::swap(p2.x, p2.y);
    }

    if (p1.x > p2.x) { // make it left−to−right
        std::swap(p1, p2);
    }

    const u32 packed_color = PackedColor(color);

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

void Renderer::DrawMesh(const Mesh* mesh, RenderMode render_mode) {
    const size_t faces_num = mesh->faces.size();
    for (size_t i = 0; i < faces_num; i+=3) {
        Vec3 v0 = mesh->vertices[mesh->faces[i]];
        Vec3 v1 = mesh->vertices[mesh->faces[i + 1]];
        Vec3 v2 = mesh->vertices[mesh->faces[i + 2]];

        if (render_mode != RenderMode::Wireframe) {
            Vec3 a = v1 - v0;
            Vec3 b = v2 - v0;
            Vec3 n = Cross(a, b);
            if (n.z >= 0) {
                continue;
            }
        }

        const ScreenVertex& one = ProjectToScreen(v0);
        const ScreenVertex& two = ProjectToScreen(v1);
        const ScreenVertex& three = ProjectToScreen(v2);

        switch(render_mode) {
            case RenderMode::Wireframe: {
                DrawLine({one.x, one.y}, {two.x, two.y}, WHITE);
                DrawLine({two.x, two.y}, {three.x, three.y}, WHITE);
                DrawLine({three.x, three.y}, {one.x, one.y}, WHITE);
                break;
            }
            case RenderMode::Solid: {
                DrawTriangle(one, two, three, WHITE);
                break;
            }
            case RenderMode::RandomColor: {
                DrawTriangle(one, two, three, RandomColor());
                break;
            }
        }

    }
}

void Renderer::DrawTriangle(ScreenVertex sv1, ScreenVertex sv2, ScreenVertex sv3, const Color& color) {
    const i32 bb_min_x = std::min(std::min(sv1.x, sv2.x), sv3.x);
    const i32 bb_min_y = std::min(std::min(sv1.y, sv2.y), sv3.y);
    const i32 bb_max_x = std::max(std::max(sv1.x, sv2.x), sv3.x);
    const i32 bb_max_y = std::max(std::max(sv1.y, sv2.y), sv3.y);

    const double total_area = TriangleAreaSigned({sv1.x, sv1.y}, {sv2.x, sv2.y}, {sv3.x, sv3.y});
    if (total_area < 1.0) {
        return;
    }

    ClearZBuffer();

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
                SetPixel(x, y, PackedColor(color));
            }
        }
    }
}

ScreenVertex Renderer::ProjectToScreen(Vec3 vertex) {
    const float z = vertex.z + 5.0f;  // push model in front of camera

    float px = vertex.x / z;
    float py = vertex.y / z;

    ScreenVertex out;
    out.x = (u16)((px + 1.0f) * 0.5f * target->width);
    out.y = (u16)((1.0f - (py + 1.0f) * 0.5f) * target->height);
    out.depth = z;

    return out;
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
