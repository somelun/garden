#pragma once

#include <cstdint>

class Application {
public:
    Application(const char* title, uint16_t width, uint16_t height);
    ~Application();

    void PresentBuffer(const class Framebuffer* framebuffer);
    void HandleEvent();

    bool IsRunning();

private:
    void CreateWindow(const char* title);
    void CloseWindow();

    struct window_impl_t* window_impl{nullptr};

    uint16_t width_;
    uint16_t height_;
};
