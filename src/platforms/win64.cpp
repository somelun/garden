#include "application.h"

#include <windows.h>
#include <iostream>


// Win64 window implementation
struct window_impl_t {
    HWND handler;
    //Framebuffer* buffer;
    bool bClosing{ false };
};

static LRESULT CALLBACK main_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
    return 0;
}

Application::Application() {
    std::cout << "Application launching...\n";
    WNDCLASS window_class;

    window_class.style = CS_HREDRAW|CS_VREDRAW;
    window_class.lpfnWndProc = main_callback;
    window_class.hInstance = GetModuleHandle(NULL);
    window_class.lpszClassName = "sandbox";

    
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

