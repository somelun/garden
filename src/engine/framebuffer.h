#pragma once

#include <cstdint>

class Framebuffer {
public:
    Framebuffer();
    Framebuffer(uint16_t w, uint16_t h);

    ~Framebuffer();

    void draw(uint16_t x, uint16_t y, unsigned char color);
    void clear();

    uint16_t get_width() const { return width; }
    uint16_t get_height() const { return height; }

    unsigned char* get_data() const { return data; }

private:
    uint16_t width;
    uint16_t height;

    unsigned char* data;
};
