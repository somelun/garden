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

    void DrawTriangle2D(Framebuffer& buffer, const Color& color, Point p1, Point p2, Point p3);
    void DrawTriangleTop(Framebuffer& buffer, const Color& color, Point p1, Point p2, Point p3);
    void DrawTriangleBottom(Framebuffer& buffer, const Color& color, Point p1, Point p2, Point p3);

    void DrawQuad(Framebuffer& buffer, const Color& color, Point p1, Point p2, Point p3, Point p4);

    std::vector<Segment> segments_;
};
