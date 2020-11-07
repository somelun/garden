#pragma once

#include "../maths.h"
#include <vector>

struct segment {

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

    std::vector<segment> segments_;
};
