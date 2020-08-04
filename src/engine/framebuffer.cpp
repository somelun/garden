#include "framebuffer.h"
#include <stdlib.h>
#include <cassert>

Framebuffer::Framebuffer()
    : Framebuffer(640, 480)
{
}

Framebuffer::Framebuffer(uint16_t w, uint16_t h)
    : width(w)
    , height(h)
{
    data = (unsigned char*)malloc(sizeof(unsigned char*) * width * height);
}

Framebuffer::~Framebuffer()
{
    free(data);
}

void Framebuffer::draw(uint16_t x, uint16_t y, unsigned char color)
{
    assert(x < width && y  < height);

    // data[] =
}

void Framebuffer::clear()
{
    size_t size = width * height / 4;
    for (size_t i = 0; i < size; i += 4)
    {
        data[i]     = 0;
        data[i + 1] = 0;
        data[i + 2] = 0;
        data[i + 3] = 255;
    }
}
