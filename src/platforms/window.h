#pragma once

#include <cstdint>


class Window {
public:
    Window(const char* title, uint16_t width, uint16_t height);
    ~Window();

private:
    class window_impl_t* window_impl;
};
