#include "buffer.h"
#include "../math/vector3.h"

#include <stdlib.h>

Buffer::Buffer() {
    width = 640;
    height = 480;

    size_t size = width * height;

    data = (unsigned char*)malloc(sizeof(unsigned char*) * size);

    for (size_t i = 0; i < size / 4; i += 4) {
        data[i] = 255;
        data[i + 1] = 0;
        data[i + 2] = 0;
        data[i + 3] = 255;
    }
}

Buffer::~Buffer() {

}
