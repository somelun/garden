#pragma once

#include "../framebuffer.h"
#include <algorithm>

#include <iostream>

/**
 * This class should not be used at all.
 * Instead use scene2d and scene3d to add new behaviors.
 */
class Scene {
public:
    virtual void update_buffer(Framebuffer& buffer) = 0;

    virtual ~Scene() = default;

protected:

    void draw_pixel(Framebuffer& buffer, uint16_t x, uint16_t y) {
        uint8_t* data = buffer.get_data();

        uint32_t index = (x * buffer.get_width() + y) * 4;

        // std::cout << x << ", " << y << ", " << index << std::endl;

        for (int i = 0; i < 4; ++i) {
            data[index + i] = 0;
        }
    }

    // https://github.com/ssloy/tinyrenderer/wiki/Lesson-1-Bresenham%E2%80%99s-Line-Drawing-Algorithm
    void draw_line(Framebuffer& buffer,
                            uint16_t x0,
                            uint16_t y0,
                            uint16_t x1,
                            uint16_t y1) {

        bool steep = false;
        if (std::abs(x0-x1) < std::abs(y0-y1)) {
            std::swap(x0, y0);
            std::swap(x1, y1);
            steep = true;
        }
        if (x0 > x1) {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }
        int dx = x1-x0;
        int dy = y1-y0;
        int derror2 = std::abs(dy)*2;
        int error2 = 0;
        int y = y0;
        for (int x=x0; x<=x1; x++) {
            if (steep) {
                draw_pixel(buffer, y, x);
            } else {
                draw_pixel(buffer, x, y);
            }
            error2 += derror2;
            if (error2 > dx) {
                y += (y1>y0?1:-1);
                error2 -= dx*2;
            }
        }
    }

};
