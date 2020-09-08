#pragma once

#include "../sandbox_math.h"

class RaceScene {
public:
    RaceScene(class Framebuffer& buffer);

    void update_buffer(double delta_time);

private:
    class Framebuffer& buffer_;

    float distance_{0.0f};
};
