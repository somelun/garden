#include "application.h"
#import <Cocoa/Cocoa.h>

#include <iostream>


// window implementation declaration
class window_impl_t {
private:
    NSWindow* handler;
};


// objective-c stuff to respond to events,
// such as window resizing, moving, exposing, and minimizing
@interface WindowDelegate : NSWindow<NSWindowDelegate>
@end

@implementation WindowDelegate {
    // window_t *_window;
}

// - (instancetype)initWithWindow:(window_t *)window {
//     self = [super init];
//     if (self != nil) {
//         _window = window;
//     }
//     return self;
// }

// windowWillClose:

- (BOOL)windowShouldClose:(NSWindow *)sender {
    (void)sender;
    // _window->should_close = 1;
    //TODO: later handle close in other place, after cleanup
    std::cout << "windowShouldClose\n";
    return YES;
}

- (void)windowWillClose:(NSNotification *)notification {
    std::cout << "windowWillClose\n";
}

@end

// objective-c stuff for drawing, printing, and handling events in an application
@interface BufferView : NSView
@end

@implementation BufferView {
    // window_t *_window;
}

- (void)drawRect:(NSRect)rect {
    [[NSColor grayColor] set];
    NSRectFill([self bounds]);
}

@end

static NSAutoreleasePool* globalAutoreleasePool = nullptr;

// public window class implementation
Application::Application () {
    if (NSApp == nil) {
        globalAutoreleasePool = [[NSAutoreleasePool alloc] init];
        [NSApplication sharedApplication];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

        // [NSApp finishLaunching];
    }
}

// window_impl_t* Application::createWindow() {
//     return nullptr;
// }

Application::~Application () {
    // delete window_impl;
}

void Application::run() {
    [NSApp run];
}

// window implementation implementation
void Application::createWindow(const char* title, uint16_t width, uint16_t height) {
    NSRect rect = NSMakeRect(0, 0, width, height);

    NSUInteger mask = NSWindowStyleMaskTitled
                    | NSWindowStyleMaskClosable
                    | NSWindowStyleMaskMiniaturizable
                    | NSWindowStyleMaskResizable;

    NSWindow* handler = [[NSWindow alloc] initWithContentRect:rect
                                          styleMask:mask
                                            backing:NSBackingStoreBuffered
                                              defer:NO];
    assert(handler != nil);
    [handler setTitle:[NSString stringWithUTF8String:title]];

    WindowDelegate* delegate = [[WindowDelegate alloc] init];
    assert(delegate != nil);
    [handler setDelegate:delegate];

    BufferView* view = [[[BufferView alloc] init] autorelease];
    assert(view != nil);
    [handler setContentView:view];
    [handler makeFirstResponder:view];

    [handler makeKeyAndOrderFront:nil];
}
