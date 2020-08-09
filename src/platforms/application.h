#pragma once

#include <cstdint>
// #include "../engine/buffer.h"

class Application {
public:
    Application();
    ~Application();

    void createWindow(const char* title, uint16_t width, uint16_t height);
    void closeWindow();

    void test_update();

    void draw_buffer(class Framebuffer* buffer);

    void handle_event();

    // Buffer* getBuffer();

    bool isRunning();

private:
    class window_impl_t* window_impl{nullptr};

};
