#include "application.h"

#include <windows.h>
#include <iostream>

WNDCLASS window_class = {};

// Win64 window implementation
struct window_impl_t {
    HWND handler;
    //Framebuffer* buffer;
    bool bClosing{ false };
};

static LRESULT CALLBACK main_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
    switch (message) {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hDc = BeginPaint(window, &ps);

        FillRect(hDc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(window, &ps);

        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    }

    return DefWindowProc(window, message, w_param, l_param);
}

Application::Application() {
    std::cout << "Application launching...\n";
    window_class = {};

    window_class.style = CS_HREDRAW|CS_VREDRAW;
    window_class.lpfnWndProc = main_callback;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance = GetModuleHandle(nullptr);
    window_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    window_class.lpszMenuName = NULL;
    window_class.lpszClassName = "sandbox";

    RegisterClass(&window_class); 
}

Application::~Application() {
    std::cout << "Application closing...\n";
}

void Application::create_window(const char* title, uint16_t width, uint16_t height) {
    if (window_impl == nullptr) {
        window_impl = new window_impl_t();
    }
 
    // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa
    window_impl->handler = CreateWindowEx(
        0,
        window_class.lpszClassName,
        "HandmadeHero",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width,
        height,
        0,
        0,
        GetModuleHandle(nullptr),
        0
    );

    ShowWindow(window_impl->handler, SW_SHOW);
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

