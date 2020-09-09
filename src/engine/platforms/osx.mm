#include "../application.h"

#import <Cocoa/Cocoa.h>
#include <iostream>

#include "../framebuffer.h"

// MacOS window implementation
struct window_impl_t {
    NSWindow* handler;
    Framebuffer* buffer;
    bool bClosing{false};   //TODO: bad name
};

// some information aboud window resize
// https://developer.apple.com/documentation/appkit/nswindowdelegate


// objective-c stuff to respond to events,
// such as window resizing, moving, exposing, and minimizing
@interface WindowDelegate : NSWindow<NSWindowDelegate>
@end

@implementation WindowDelegate {
    window_impl_t* window_;
}

- (instancetype)initWithWindow:(window_impl_t *)in_window {
    self = [super init];
    if (self != nil) {
        window_ = in_window;
    }
    return self;
}

- (BOOL)windowShouldClose:(NSWindow *)sender {
    (void)sender;
    window_->bClosing = true;
    return NO;
}

- (void)windowWillClose:(NSNotification *)notification {
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
    uint8_t* data = window_->buffer->get_data();

    NSBitmapImageRep *image_rep = [[[NSBitmapImageRep alloc]
            initWithBitmapDataPlanes:&(data)
                          pixelsWide:window_->buffer->get_width()
                          pixelsHigh:window_->buffer->get_height()
                       bitsPerSample:8
                     samplesPerPixel:3
                            hasAlpha:NO
                            isPlanar:NO
                      colorSpaceName:NSCalibratedRGBColorSpace
                         bytesPerRow:window_->buffer->get_width() * 4
                        bitsPerPixel:32] autorelease];

    NSImage *image = [[[NSImage alloc] init] autorelease];
    [image addRepresentation:image_rep];
    [image drawInRect:rect];
}

- (void)keyDown:(NSEvent *)event {
    NSString* chars = [event characters];

    [self interpretKeyEvents:[NSArray arrayWithObject:event]];
}

- (void)keyUp:(NSEvent *)event {
    //
}

- (void)mouseDown:(NSEvent *)event {
}

- (void)mouseUp:(NSEvent *)event {
}

@end

// static NSAutoreleasePool* globalAutoreleasePool = nullptr;

// public window class implementation
Application::Application() {
    std::cout << "Application launching...\n";
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
    std::cout << "Application closing...\n";
}

// window implementation
void Application::create_window(const char* title, uint16_t width, uint16_t height) {
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

    WindowDelegate* delegate = [[WindowDelegate alloc] initWithWindow:window_impl];
    assert(delegate != nil);
    [window_impl->handler setDelegate:delegate];

    BufferView* view = [[[BufferView alloc] initWithWindow:window_impl] autorelease];
    assert(view != nil);
    [window_impl->handler setContentView:view];
    [window_impl->handler makeFirstResponder:view];

    [window_impl->handler makeKeyAndOrderFront:nil];
}

void Application::close_window() {
    [window_impl->handler orderOut:nil];

    [[window_impl->handler delegate] release];
    [window_impl->handler close];

    // [g_autoreleasepool drain];
    // g_autoreleasepool = [[NSAutoreleasePool alloc] init];

    delete window_impl;
}

void Application::draw_buffer(Framebuffer* buffer) {
    window_impl->buffer = buffer;
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

bool Application::is_running() {
    return !window_impl->bClosing;
}
