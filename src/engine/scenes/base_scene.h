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

    void draw_pixel(Framebuffer& buffer, uint16_t x, uint16_t y) {
        uint8_t* data = buffer.get_data();
        uint16_t index = (y * buffer.get_width() + x) * 4;
        for (int i = 0; i < 4; ++i) {
            data[index + i] = 255;
        }
    }

};
