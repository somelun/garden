#pragma once

#include "framebuffer.h"
#include "math.h"
#include <algorithm>
#include <cstdlib>


static void fill(Framebuffer& buffer, const color_t& color) {
    uint8_t* data = buffer.get_data();

    size_t size = buffer.get_width() * buffer.get_height() * 4;
    for (size_t i = 0; i < size; i += 4) {
        data[i]     = color[0];
        data[i + 1] = color[1];
        data[i + 2] = color[2];
        data[i + 3] = color[3];
    }
}

static void draw_pixel(Framebuffer& buffer, uint16_t x, uint16_t y, const color_t& color) {
    uint8_t* data = buffer.get_data();

    uint32_t index = (y * buffer.get_width() + x) * 4;
    for (int i = 0; i < 4; ++i) {
        data[index + i] = color[i];
    }
}

// https://github.com/ssloy/tinyrenderer/wiki/Lesson-1-Bresenham%E2%80%99s-Line-Drawing-Algorithm
static void draw_line(Framebuffer& buffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, const color_t& color) {
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int16_t dx = x1 - x0;
    int16_t dy = y1 - y0;
    uint16_t derror2 = std::abs(dy) * 2;
    uint16_t error2 = 0;
    uint16_t y = y0;
    for (size_t x = x0; x <= x1; ++x) {
        if (steep) {
            draw_pixel(buffer, y, x, color);
        } else {
            draw_pixel(buffer, x, y, color);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0 ? 1: -1);
            error2 -= dx * 2;
        }
    }
}
