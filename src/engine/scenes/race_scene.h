#pragma once

#include <vector>
#include "../maths.h"

struct Bucket {
    int yMax;
    int yMin;
    int x;
    int sign;
    int dX;
    int dY;
    double sum;
};

struct Vertex {
    int x;
    int y;
};

struct Segment {
    vector3f world_coords;  // world coordinates
    vector3f screen_coords;  // screen coordinates
    color_t color;
};

class RaceScene {
public:
    RaceScene(class Framebuffer& buffer);

    void update(double dt);

private:
    class Framebuffer& buffer_;

    float distance_{0.0f};
    float curvature_{0.0f};

    uint16_t width_{0};
    uint16_t height_{0};

    std::vector<std::pair<float, float>> track_data_;

    void update2(double dt);
    void draw_triangle_flat_bottom(Framebuffer& buffer, const color_t& color, vector2i p0, vector2i p1, vector2i p2);
    void draw_triangle_flat_top(Framebuffer& buffer, const color_t& color, vector2i p0, vector2i p1, vector2i p2);

    void DrawTriangle2D(Framebuffer& buffer, const Color& color, Point p1, Point p2, Point p3);
    void DrawTriagnleTop(Framebuffer& buffer, const Color& color, Point p1, Point p2, Point p3);
    void DrawTriangleBottom(Framebuffer& buffer, const Color& color, Point p1, Point p2, Point p3);

    std::vector<Segment> segments_;
};
