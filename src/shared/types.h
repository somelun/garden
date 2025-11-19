#pragma once

#include <stdint.h>
#include <stdlib.h>

#define PI 3.14159265359f

typedef int8_t    i8;   // signed 8-bit integer
typedef int16_t   i16;  // signed 16-bit integer
typedef int32_t   i32;  // signed 32-bit integer
typedef uint8_t   u8;   // unsigned 8-bit integer
typedef uint16_t  u16;  // unsigned 16-bit integer
typedef uint32_t  u32;  // unsigned 32-bit integer

struct Color {
    u8 r, g, b, a;
};

inline uint32_t PackedColor(const Color& color) {
    return ((u32)(color.a & 0xFF) << 24) |
           ((u32)(color.b & 0xFF) << 16) |
           ((u32)(color.g & 0xFF) << 8)  |
           ((u32)(color.r & 0xFF));
}

inline Color RandomColor() {
    return {
        static_cast<u8>(rand() % 255),
        static_cast<u8>(rand() % 255),
        static_cast<u8>(rand() % 255),
        255
    };
}

#define RED     Color{255, 0, 0, 255}
#define GREEN   Color{0, 255, 0, 255}
#define BLUE    Color{0, 0, 255, 255}
#define WHITE   Color{255, 255, 255, 255}

struct Framebuffer {
    u16 width;
    u16 height;

    u32* data;
};
