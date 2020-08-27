#include "race_scene.h"
#include <stdlib.h>

#include "../framebuffer.h"

void RaceScene::update_buffer(Framebuffer& buffer) {
    uint8_t* data = buffer.get_data();

    size_t size = buffer.get_width() * buffer.get_height() * 4;
    for (size_t i = 0; i < size; i += 4) {
        data[i] += 1;
        data[i + 1] -= 2;
        data[i + 2] += 1;
    }

    draw_line(buffer, 0, 0, 400, 400);
}
