#pragma once

#include "../sandbox_math.h"
#include <vector>
// #include <pair>

class RaceScene {
public:
    RaceScene(class Framebuffer& buffer);

    void update_buffer(double delta_time);

private:
    class Framebuffer& buffer_;

    float distance_{0.0f};

    std::vector<std::pair<float, float>> track_data;

    float curvature_ = 0.0f;
};
