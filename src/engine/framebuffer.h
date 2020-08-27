#pragma once

#include <cstdint>
#include <stdlib.h>


class Framebuffer {
public:
    Framebuffer() : Framebuffer(640, 480) {}
    Framebuffer(uint16_t w, uint16_t h) : width(w), height(h) {
        data = new uint8_t[width * height *  4];
    }

    ~Framebuffer() {
        delete [] data;
    }

    uint8_t& operator()(size_t x, size_t y) {
        return data[y * width + x];
    }

    uint8_t operator()(size_t x, size_t y) const {
        return data[y * width + x];
    }

    void clear() {
        size_t size = width * height * 4;
        for (size_t i = 0; i < size; i += 4) {
            data[i]     = 0;
            data[i + 1] = 0;
            data[i + 2] = 0;
            data[i + 3] = 255;
        }
    }

    constexpr uint16_t get_width() const { return width; }
    constexpr uint16_t get_height() const { return height; }

    uint8_t* get_data() const { return data; }

private:
    uint16_t width;
    uint16_t height;

    uint8_t* data;

};
