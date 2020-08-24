#pragma once

#include <cstdint>

class Framebuffer {
public:
    Framebuffer();
    Framebuffer(uint16_t w, uint16_t h);
    Framebuffer(uint16_t w, uint16_t h, uint16_t pw, uint16_t ph);

    ~Framebuffer();

    void draw(uint16_t x, uint16_t y, unsigned char color);
    void clear();

    constexpr uint16_t get_width() const { return width * pixel_width; }
    constexpr uint16_t get_height() const { return height * pixel_height; }

    uint8_t* get_data() const { return data; }

private:
    uint16_t width;
    uint16_t height;

    uint16_t pixel_width;
    uint16_t pixel_height;

    uint8_t* data;
};
