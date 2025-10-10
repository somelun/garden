#pragma once

#include <cstdint>
#include <string.h> // required for memset


class Framebuffer {
public:
    Framebuffer() : Framebuffer(640, 480) {}
    Framebuffer(uint16_t w, uint16_t h) : width_(w), height_(h) {
        data_ = new uint8_t[width_ * height_ *  4];
    }

    ~Framebuffer() {
        delete [] data_;
    }

    uint8_t& operator()(const size_t x, const size_t y) {
        return data_[y * width_ + x];
    }

    uint8_t operator()(const size_t x, const size_t y) const {
        return data_[y * width_ + x];
    }

    void clear() {
        size_t size = width_ * height_ * 4;
        memset(data_, 0, size * sizeof(*data_));
    }

    constexpr uint16_t get_width() const { return width_; }
    constexpr uint16_t get_height() const { return height_; }

    uint8_t* get_data() const { return data_; }

private:
    uint16_t width_;
    uint16_t height_;

    uint8_t* data_;
};
