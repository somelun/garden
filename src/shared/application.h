#pragma once

// #include <cstdint>
#include "types.h"

struct WindowImpl;

class Application {
public:
    Application(const char* title, u16 width, u16 height);
    ~Application();

    Framebuffer* GetFrameBuffer() const;

    void PresentBuffer();
    void HandleEvent();

    bool IsRunning() const;

private:
    void* platform_window_ = nullptr;
};
