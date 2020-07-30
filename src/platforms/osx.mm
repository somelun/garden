#include "application.h"
#import <Cocoa/Cocoa.h>

#include <iostream>


// window implementation declaration
class window_impl_t {
public:
    NSWindow* handler;
};

// some information aboud window resize
// https://developer.apple.com/documentation/appkit/nswindowdelegate


// objective-c stuff to respond to events,
// such as window resizing, moving, exposing, and minimizing
@interface WindowDelegate : NSWindow<NSWindowDelegate>
@end

@implementation WindowDelegate {
}

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
}

- (void)drawRect:(NSRect)rect {
    [[NSColor grayColor] set];
    NSRectFill([self bounds]);
}

- (void)mouseDown:(NSEvent *)event {
}

- (void)mouseUp:(NSEvent *)event {
}

@end

// static NSAutoreleasePool* globalAutoreleasePool = nullptr;

// public window class implementation
Application::Application() {
    std::cout << "Application\n";
    if (NSApp == nil) {
        // globalAutoreleasePool = [[NSAutoreleasePool alloc] init];
        [NSApplication sharedApplication];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

        id menubar = [[NSMenu new] autorelease];
        id appMenuItem = [[NSMenuItem new] autorelease];
        [menubar addItem:appMenuItem];
        [NSApp setMainMenu:menubar];

        id appMenu = [[NSMenu new] autorelease];
        id appName = [[NSProcessInfo processInfo] processName];
        id quitTitle = [@"Quit " stringByAppendingString:appName];
        id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle
                                                      action:@selector(terminate:) keyEquivalent:@"q"] autorelease];
        [appMenu addItem:quitMenuItem];
        [appMenuItem setSubmenu:appMenu];

        [NSApp finishLaunching];
    }
}

Application::~Application () {
    std::cout << "~Application\n";
    if (window_impl != nullptr) {
        delete window_impl;
    }
}

// window implementation
void Application::createWindow(const char* title, uint16_t width, uint16_t height) {
    if (window_impl == nullptr) {
        window_impl = new window_impl_t();
    }

    NSRect rect = NSMakeRect(0, 0, width, height);

    NSUInteger mask = NSWindowStyleMaskTitled
                    | NSWindowStyleMaskClosable
                    | NSWindowStyleMaskMiniaturizable
                    | NSWindowStyleMaskResizable;

    window_impl->handler = [[NSWindow alloc] initWithContentRect:rect
                                          styleMask:mask
                                            backing:NSBackingStoreBuffered
                                              defer:NO];
    assert(window_impl->handler != nil);
    [window_impl->handler setTitle:[NSString stringWithUTF8String:title]];

    WindowDelegate* delegate = [[WindowDelegate alloc] init];
    assert(delegate != nil);
    [window_impl->handler setDelegate:delegate];

    BufferView* view = [[[BufferView alloc] init] autorelease];
    assert(view != nil);
    [window_impl->handler setContentView:view];
    [window_impl->handler makeFirstResponder:view];

    [window_impl->handler makeKeyAndOrderFront:nil];
}

void Application::handle_event() {
    @autoreleasepool {
        NSEvent* event = nil;
        do {
            event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                       untilDate:[NSDate distantPast]
                                          inMode:NSDefaultRunLoopMode
                                         dequeue:YES];
            [NSApp sendEvent:event];
        } while(event);
    }
}
