#pragma once

#include <cstdint>
class Buffer {
public:
    // unsigned char* getData() {
    //     return data;
    // }

    Buffer();
    ~Buffer();

    unsigned char* data;
private:
    uint16_t width;
    uint16_t height;

};
