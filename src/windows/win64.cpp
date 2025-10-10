#include <windows.h>
#include <iostream>

// MS Windows used this define for I don't know what reason, but I don't want
// to rename my function, thats why I undefine it firt
 #undef CreateWindow

#include "../application.h"


static const char* const WINDOW_ENTRY_NAME = "Entry";


WNDCLASS WindowClass = {};

// Win64 window implementation
struct window_impl_t {
    HWND handler;
    Framebuffer* buffer;
    bool bClosing{ false };
};

static LRESULT CALLBACK MainCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    window_impl_t* window_impl = (window_impl_t*)GetProp(window, WINDOW_ENTRY_NAME);

    switch (message) {
        case WM_PAINT: {
            PAINTSTRUCT ps;

            HDC DeviceContext = BeginPaint(window, &ps);
            FillRect(DeviceContext, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(window, &ps);

            return 0;
        }

        case WM_CLOSE: {
            window_impl->bClosing = true;
            return 0;
        }

        case WM_DESTROY: {
            window_impl->bClosing = true;
            PostQuitMessage(0); // not sure if I need this call here
            return 0;
        }
    }

    return DefWindowProc(window, message, wParam, lParam);
}

Application::Application(const char* title, uint16_t width, uint16_t height) 
    : width_(width)
    , height_(height) {
    std::cout << "Application launching...\n";

    WindowClass = {};
    WindowClass.style = CS_HREDRAW|CS_VREDRAW;
    WindowClass.lpfnWndProc = MainCallback;
    WindowClass.cbClsExtra = 0;
    WindowClass.cbWndExtra = 0;
    WindowClass.hInstance = GetModuleHandle(nullptr);
    // WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    // WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WindowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WindowClass.lpszMenuName = NULL;
    WindowClass.lpszClassName = title;

    if (RegisterClass(&WindowClass)) {
        CreateWindow(title);
    }
}

Application::~Application() {
    std::cout << "Application closing...\n";
}

void Application::CreateWindow(const char* title) {
    if (window_impl == nullptr) {
        window_impl = new window_impl_t();
    }

    // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa
    window_impl->handler = CreateWindowEx(
        0,
        WindowClass.lpszClassName,
        title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, // x
        CW_USEDEFAULT, // y
        width_,
        height_,
        0, // parent window
        0, // menu
        GetModuleHandle(nullptr), // instance
        0
    );

    if (window_impl->handler) {
        SetProp(window_impl->handler, WINDOW_ENTRY_NAME, window_impl);
        ShowWindow(window_impl->handler, SW_SHOW);
    }
}

void Application::CloseWindow() {
    delete window_impl;
}

void Application::PresentBuffer(const class Framebuffer* buffer) {
    //HDC window_dc = GetDC(window_impl->handler);
    //HDC memory_dc = window->memory_dc;
    //image_t* surface = window->surface;
    //int width = surface->width;
    //int height = surface->height;
    //BitBlt(window_dc, 0, 0, width, height, memory_dc, 0, 0, SRCCOPY);
    //ReleaseDC(window->handle, window_dc);
}

void Application::HandleEvent() {
    MSG message;
    while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

void Application::SetTitle(const char* title) {
    //
}

bool Application::IsRunning() {
    return !window_impl->bClosing;
}
