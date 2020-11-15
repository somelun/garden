#pragma once

#include <vector>
#include "../maths.h"

struct Segment {
    // we store only z points for segments, because y point is always 0 and
    // x point is always screen_width / 2
    float closest{0.0};
    float farthest{0.0};
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

    std::vector<Segment> segments_;
};
