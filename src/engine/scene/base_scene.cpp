#include "base_scene.h"
#include <stdlib.h>

#include "../framebuffer.h"

void Scene::update_buffer(Framebuffer& buffer)
{
    size_t size = buffer.getWidth() * buffer.getHeight() * 4;

    for (size_t i = 0; i < size; i += 4)
    {
        buffer.data[i] += 1;
        buffer.data[i + 1] -= 2;
        buffer.data[i + 2] += 1;
    }
}
