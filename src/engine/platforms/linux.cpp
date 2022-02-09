#include "../application.h"

#include <iostream>


// linux window implementation
struct window_impl_t {
    bool bClosing{false};
};

Application::Application(const char* title, uint16_t width, uint16_t height) {
    std::cout << "Application launching...\n";
}

Application::~Application() {
    std::cout << "Application closing...\n";
}

void Application::CreateWindow(const char* title) {
    if (window_impl == nullptr) {
        window_impl = new window_impl_t();
    }
}

void Application::CloseWindow() {
    delete window_impl;
}

void Application::PresentBuffer(const Framebuffer* framebuffer) {
    //
}

void Application::HandleEvent() {
    //
}

bool Application::IsRunning() {
    return !window_impl->bClosing;
}

