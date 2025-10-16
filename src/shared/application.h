#pragma once

#include <cstdint>

struct Framebuffer;
struct WindowImpl;

class Application {
public:
    Application(const char* title, uint16_t width, uint16_t height);
    ~Application();

    Framebuffer* GetFrameBuffer() const;

    void PresentBuffer();
    void HandleEvent();

    bool IsRunning() const;

private:
    void* platform_window_ = nullptr;
};
