#include "framebuffer.h"
#include <stdlib.h>
#include <cassert>

Framebuffer::Framebuffer()
    : Framebuffer(640, 480) {
}

Framebuffer::Framebuffer(uint16_t w, uint16_t h)
    : Framebuffer(w, h, 1, 1) {
}

Framebuffer::Framebuffer(uint16_t w, uint16_t h, uint16_t pw, uint16_t ph)
    : width(w)
    , height(h)
    , pixel_width(pw)
    , pixel_height(ph) {
    data = (unsigned char*)malloc(sizeof(unsigned char*) * width * height * pixel_width * pixel_height *  4);
}

Framebuffer::~Framebuffer() {
    free(data);
}

void Framebuffer::draw(uint16_t x, uint16_t y, unsigned char color) {
    assert(x < width && y  < height);

    (void)color;
}

void Framebuffer::clear() {
    size_t size = width * height * 4;
    for (size_t i = 0; i < size; i += 4) {
        data[i]     = 0;
        data[i + 1] = 0;
        data[i + 2] = 0;
        data[i + 3] = 255;
    }
}
