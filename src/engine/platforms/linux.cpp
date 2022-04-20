#include "../application.h"
#include "../framebuffer.h"

#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

static Display *display = nullptr;

static Atom protocols = None;
static Atom delete_window = None;

// linux window implementation
struct window_impl_t {
    Window handler;
    Framebuffer* buffer;
    XImage* ximage;
    bool bClosing{false};
};

Application::Application(const char* title, uint16_t width, uint16_t height)
    : width_(width)
    , height_(height) {
    std::cout << "Application launching...\n";

    if (display == nullptr) {
        display = XOpenDisplay(nullptr);

        CreateWindow(title);
    }
}

Application::~Application() {
    CloseWindow();
    std::cout << "Application closing...\n";
}

void Application::CreateWindow(const char* title) {
    if (window_impl == nullptr) {
        window_impl = new window_impl_t();
    }

    int screen = XDefaultScreen(display);
    Window root = XRootWindow(display, screen);

    unsigned long border = XWhitePixel(display, screen);
    unsigned long background = XBlackPixel(display, screen);

    window_impl->handler = XCreateSimpleWindow(display, root, 0, 0,
                                 width_, height_, 0,
                                 border, background);

    XSizeHints* size_hints = XAllocSizeHints();
    size_hints->flags = PMinSize | PMaxSize;
    size_hints->min_width = width_;
    size_hints->max_width = width_;
    size_hints->min_height = height_;
    size_hints->max_height = height_;
    XSetWMNormalHints(display, window_impl->handler, size_hints);
    XFree(size_hints);

    XClassHint *class_hint = XAllocClassHint();
    class_hint->res_name = (char*)title;
    class_hint->res_class = (char*)title;
    XSetClassHint(display, window_impl->handler, class_hint);
    XFree(class_hint);

    // we need to subscribe to this event, or nothing happens
    protocols = XInternAtom(display, "WM_PROTOCOLS", false);
    delete_window = XInternAtom(display, "WM_DELETE_WINDOW", false);
    XSetWMProtocols(display, window_impl->handler, &delete_window, 1);

    Visual* visual = XDefaultVisual(display, screen);
    const int depth = XDefaultDepth(display, screen);

    Framebuffer* fb = new Framebuffer(width_, height_);

    window_impl->ximage = XCreateImage(
        display,
        visual,
        depth,
        ZPixmap,
        0,
        (char*)fb->get_data(),
        width_,
        height_,
        32,
        0
    );

    XMapWindow(display, window_impl->handler);

    XFlush(display);
}

void Application::CloseWindow() {
    delete window_impl;
}

void Application::PresentBuffer(const Framebuffer* framebuffer) {
    int screen = XDefaultScreen(display);
    GC gc = XDefaultGC(display, screen);

    window_impl->ximage->data = (char*)framebuffer->get_data();

    //TODO: someday check this with proper linux
    XPutImage(
        display,
        window_impl->handler,
        gc,
        window_impl->ximage,
        0, 0, 0, 0,
        framebuffer->get_width(),
        framebuffer->get_height()
    );

    XFlush(display);
}

static void ProcessEvent(window_impl_t& impl, XEvent *event);

void Application::HandleEvent() {
    int count = XPending(display);
    while (count > 0) {
        XEvent event;
        XNextEvent(display, &event);
        ProcessEvent(*window_impl, &event);
        count -= 1;
    }
    XFlush(display);
}

bool Application::IsRunning() {
    return !window_impl->bClosing;
}

static void ProcessEvent(window_impl_t& impl, XEvent *event) {
    if (event->type == ClientMessage) {
        if (protocols == None) {
            return;
        }

        if (event->xclient.message_type == protocols) {
            Atom protocol = event->xclient.data.l[0];
            if (protocol == delete_window) {
                impl.bClosing = true;
            }
        }
    }
}

