#pragma once

#include <cstdint>

class Application {
public:
    Application(const char* title, uint16_t width, uint16_t height);
    ~Application();

    struct Framebuffer* GetFrameBuffer() const;

    void PresentBuffer(const struct Framebuffer* framebuffer);
    void HandleEvent();

    bool IsRunning();

private:
    void CreateWindowImpl(const char* title, uint16_t width, uint16_t height);
    void CloseWindowImpl();

    struct WindowImpl* window_impl{nullptr};
};
