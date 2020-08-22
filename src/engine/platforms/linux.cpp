#include "application.h"

#include <iostream>


// linux window implementation
struct window_impl_t {
    bool bClosing{false};
};

Application::Application() {
    std::cout << "Application launching...\n";
}

Application::~Application() {
    std::cout << "Application closing...\n";
}

void Application::create_window(const char* title, uint16_t width, uint16_t height) {
    if (window_impl == nullptr) {
        window_impl = new window_impl_t();
    }
}

void Application::close_window() {
    delete window_impl;
}

void Application::draw_buffer(class Framebuffer* buffer) {
    //
}

void Application::handle_event() {
    //
}

bool Application::is_running() {
    return !window_impl->bClosing;
}

