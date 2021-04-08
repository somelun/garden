#pragma once

#include <cstdint>

class Application {
public:
    Application(const char* title, uint16_t width, uint16_t height);
    ~Application();

    // TODO: move this function to private

    void draw_buffer(const class Framebuffer* framebuffer);

    void handle_event();

    bool is_running();

private:
    void create_window(const char* title);
    void close_window();

    struct window_impl_t* window_impl{nullptr};

    uint16_t width_;
    uint16_t height_;
};
