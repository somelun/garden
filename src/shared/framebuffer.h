#pragma once

#include <cstdint>

struct Framebuffer {
    uint16_t width;
    uint16_t height;

    uint32_t* data;
};
