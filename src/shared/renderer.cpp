#include "renderer.h"

#include <utility> // std::swap
#include <cstring> // memcpy

#define USE_BARYCENTRIC_FOR_RASTERIZATION 1

void Renderer::SetTarget(Framebuffer* fb) {
    target = fb;
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
void Renderer::DrawLine(Point2D p1, Point2D p2, const Color& color) {
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

void Renderer::DrawMesh(const Mesh* mesh) {
    const size_t faces_num = mesh->faces.size();
    for (size_t i = 0; i < faces_num; i+=3) {
        Point2D one = ProjectToScreen(mesh->vertices[mesh->faces[i]]);
        Point2D two = ProjectToScreen(mesh->vertices[mesh->faces[i + 1]]);
        Point2D three = ProjectToScreen(mesh->vertices[mesh->faces[i + 2]]);
        // DrawLine(One, Two, WHITE);
        // DrawLine(Two, Three, WHITE);
        // DrawLine(Three, One, WHITE);
        DrawTriangle(one, two, three, WHITE);
    }

    const size_t vertices_num = mesh->vertices.size();
    for (size_t i = 0; i < vertices_num; ++i) {
        Vec3f vertex = mesh->vertices[i];
        Point2D projected = ProjectToScreen(vertex);
        SetPixel(projected.x, projected.y, PackedColor(RED));
    }
}

void Renderer::DrawTriangle(Point2D p1, Point2D p2, Point2D p3, const Color& color) {
#if USE_BARYCENTRIC_FOR_RASTERIZATION
    const i32 bb_min_x = std::min(std::min(p1.x, p2.x), p3.x);
    const i32 bb_min_y = std::min(std::min(p1.y, p2.y), p3.y);
    const i32 bb_max_x = std::max(std::max(p1.x, p2.x), p3.x);
    const i32 bb_max_y = std::max(std::max(p1.y, p2.y), p3.y);

    const double total_area = TriangleAreaSigned(p1, p2, p3);
    if (total_area < 1.0) {
        return;
    }

    for (i32 x = bb_min_x; x <= bb_max_x; ++x) {
        for (i32 y = bb_min_y; y<=bb_max_y; ++y) {
            double alpha = TriangleAreaSigned({x, y}, p2, p3) / total_area;
            double beta  = TriangleAreaSigned({x, y}, p3, p1) / total_area;
            double gamma = TriangleAreaSigned({x, y}, p1, p2) / total_area;
            if (alpha < 0 || beta < 0 || gamma < 0) {
                continue;
            }

            unsigned char r = static_cast<unsigned char>(alpha * RED.r + beta * GREEN.r + gamma * BLUE.r);
            unsigned char g = static_cast<unsigned char>(alpha * RED.g + beta * GREEN.g + gamma * BLUE.g);
            unsigned char b = static_cast<unsigned char>(alpha * RED.b + beta * GREEN.b + gamma * BLUE.b);

            SetPixel(x, y, PackedColor({r, g, b}));
            // SetPixel(x, y, PackedColor(color));
        }
    }
#else
    if (p2.y < p1.y) {
        std::swap(p1, p2);
    }

    if (p3.y < p1.y) {
        std::swap(p1, p3);
    }

    if (p3.y < p2.y) {
        std::swap(p2, p3);
    }

    i32 total_height = p3.y - p1.y;
    if (total_height == 0) {
        return;
    }

    for (i32 i = 0; i <= total_height; i++) {
        bool second_half = (i >= p2.y - p1.y) && (p2.y > p1.y);
        i32 segment_height = second_half ? (p3.y - p2.y) : (p2.y - p1.y);

        if (segment_height <= 0) {
            continue;
        }

        float alpha = (float)i / total_height;
        float beta = second_half 
            ? (float)(i - (p2.y - p1.y)) / segment_height
            : (float)i / segment_height;

        Point2D A = p1 + (p3 - p1) * alpha;
        Point2D B = second_half ? p2 + (p3 - p2) * beta : p1 + (p2 - p1) * beta;

        if (A.x > B.x) {
            std::swap(A, B);
        }

        for (int x = A.x; x <= B.x; x++) {
            SetPixel(x, p1.y + i, PackedColor(color));
        }
    }
#endif // #if USE_BARYCENTRIC_FOR_RASTERIZATION
}

Point2D Renderer::ProjectToScreen(Point3D vertex) {
    const float z = vertex.z + 5.0f;  // push model in front of camera

    float px = vertex.x / z;
    float py = vertex.y / z;

    return {
        (u16)((px + 1.0f) * 0.5f * target->width),
        (u16)((1.0f - (py + 1.0f) * 0.5f) * target->height)
    };
}

void Renderer::SetPixel(const u32 x, const u32 y, const u32 packed_color) {
    const u32 index = y * target->width + x;
    target->data[index] = packed_color;
}

// variation of https://en.wikipedia.org/wiki/Shoelace_formula
double Renderer::TriangleAreaSigned(const Point2D& p1, const Point2D& p2, const Point2D& p3) {
    return 0.5 * ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
}
