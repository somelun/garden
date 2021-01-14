#pragma once

#include <cstdint>

class Application {
public:
    Application(uint16_t width, uint16_t height);
    ~Application();

    void create_window(const char* title);
    void close_window();

    void draw_buffer(class Framebuffer* buffer);

    void handle_event();

    bool is_running();

private:
    struct window_impl_t* window_impl{nullptr};

    uint16_t width_;
    uint16_t height_;
};
