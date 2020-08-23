#pragma once

#include "../framebuffer.h"

/**
 * This class should not be used at all. 
 * Instead use scene2d and scene3d to add new behaviors. 
 */
class Scene {
public:
    virtual void update_buffer(Framebuffer& buffer) = 0;

    virtual ~Scene() = default;

protected:

    void draw_pixel(Framebuffer& buffer, int8_t x, uint8_t y) {
        uint16_t index = (y * buffer.get_width() + x) * 4;
        unsigned char* data = buffer.get_data();
        for (int i = 0; i < 4; ++i) {
            data[index + i] = 255;
        }
    }

};
