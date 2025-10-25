#pragma once

#include "stdint.h"

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
           ((u32)(color.r & 0xFF) << 16) |
           ((u32)(color.g & 0xFF) << 8)  |
           ((u32)(color.b & 0xFF));
}
