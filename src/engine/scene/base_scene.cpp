#include "base_scene.h"
#include <stdlib.h>

void BaseScene::fill_buffer(class Buffer& buffer) {
    size_t size = buffer.width * buffer.height / 4;

    for (size_t i = 0; i < size; i += 4) {
        buffer.data[i] += 1;
    }
}
