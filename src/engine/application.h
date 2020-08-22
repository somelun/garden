#pragma once

#include <cstdint>

class Application {
public:
    Application();
    ~Application();

    void create_window(const char* title, uint16_t width, uint16_t height);
    void close_window();

    void draw_buffer(class Framebuffer* buffer);

    void handle_event();

    bool is_running();

private:
    struct window_impl_t* window_impl{nullptr};
};
