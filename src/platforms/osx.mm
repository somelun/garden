#import <Cocoa/Cocoa.h>

#include "application.h"
#include "../engine/buffer.h"

#include <iostream>


// os x window representation
class window_impl_t {
public:
    NSWindow* handler;
    Buffer* buffer;
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
    window_impl_t* window_;
}

- (instancetype)initWithWindow:(window_impl_t *)in_window {
    self = [super init];
    if (self != nil) {
        window_ = in_window;
    }
    return self;
}

- (void)drawRect:(NSRect)rect {
    Buffer* buffer = window_->buffer;

    NSBitmapImageRep *image_rep = [[[NSBitmapImageRep alloc]
            initWithBitmapDataPlanes:&(buffer->data)
                          pixelsWide:100
                          pixelsHigh:100
                       bitsPerSample:8
                     samplesPerPixel:3
                            hasAlpha:NO
                            isPlanar:NO
                      colorSpaceName:NSCalibratedRGBColorSpace
                         bytesPerRow:400
                        bitsPerPixel:32] autorelease];

    NSImage *image = [[[NSImage alloc] init] autorelease];
    [image addRepresentation:image_rep];
    [image drawInRect:rect];
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

    window_impl->buffer = new Buffer();

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

    BufferView* view = [[[BufferView alloc] initWithWindow:window_impl] autorelease];
    assert(view != nil);
    [window_impl->handler setContentView:view];
    [window_impl->handler makeFirstResponder:view];

    [window_impl->handler makeKeyAndOrderFront:nil];
}

void Application::test_update() {
    [[window_impl->handler contentView] setNeedsDisplay:YES];
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

Buffer* Application::getBuffer() {
    return window_impl->buffer;
}
