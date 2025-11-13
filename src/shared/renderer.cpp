#include "renderer.h"

#include <utility> // std::swap
#include <cstring> // memcpy

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
        Point2D One = ProjectToScreen(mesh->vertices[mesh->faces[i]]);
        Point2D Two = ProjectToScreen(mesh->vertices[mesh->faces[i + 1]]);
        Point2D Three = ProjectToScreen(mesh->vertices[mesh->faces[i + 2]]);
        // DrawLine(One, Two, WHITE);
        // DrawLine(Two, Three, WHITE);
        // DrawLine(Three, One, WHITE);
        DrawTriangle(One, Two, Three, WHITE);
    }

    const size_t vertices_num = mesh->vertices.size();
    for (size_t i = 0; i < vertices_num; ++i) {
        Vec3f vertex = mesh->vertices[i];
        Point2D projected = ProjectToScreen(vertex);
        SetPixel(projected.x, projected.y, PackedColor(RED));
    }
}

void Renderer::DrawTriangle(Point2D p1, Point2D p2, Point2D p3, const Color& color) {
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
}

void Renderer::SetPixel(const u32 x, const u32 y, const u32 packed_color) {
    const u32 index = y * target->width + x;
    target->data[index] = packed_color;
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
