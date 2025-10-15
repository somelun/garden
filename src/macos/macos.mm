#include "../shared/application.h"
#include "../shared/framebuffer.h"

#import <Cocoa/Cocoa.h>
#include <iostream>

// MacOS window implementation
struct WindowImpl {
    NSWindow* handler = nil;
    Framebuffer* buffer = nullptr;
    bool should_close = false;
};

// some information aboud window resize
// https://developer.apple.com/documentation/appkit/nswindowdelegate


// objective-c stuff to respond to events,
// such as window resizing, moving, exposing, and minimizing
@interface WindowDelegate : NSWindow<NSWindowDelegate>
@end

@implementation WindowDelegate {
    WindowImpl* window_;
}

- (instancetype)initWithWindow:(WindowImpl *)in_window {
    self = [super init];
    if (self != nil) {
        window_ = in_window;
    }
    return self;
}

- (BOOL)windowShouldClose:(NSWindow *)sender {
    (void)sender;
    window_->should_close = true;
    return NO;
}

- (void)windowWillClose:(NSNotification *)notification {
    (void)notification;
}

@end

// objective-c stuff for drawing, printing, and handling events in an application
@interface BufferView : NSView
@end

@implementation BufferView {
    WindowImpl* window_;
}

- (instancetype)initWithWindow:(WindowImpl *)in_window {
    self = [super init];
    if (self != nil) {
        window_ = in_window;
    }
    return self;
}

- (void)drawRect:(NSRect)rect {
    // FIXME: hmm, doesn't look good
    if (window_->buffer == nullptr) {
        return;
    }

    uint32_t* data = window_->buffer->data_;
    uint8_t *planes[1] = { (unsigned char *)data };

    NSBitmapImageRep *image_rep = [[[NSBitmapImageRep alloc]
            initWithBitmapDataPlanes:planes
                          pixelsWide:window_->buffer->width_
                          pixelsHigh:window_->buffer->height_
                       bitsPerSample:8
                     samplesPerPixel:4
                            hasAlpha:YES
                            isPlanar:NO
                      colorSpaceName:NSCalibratedRGBColorSpace
                         bytesPerRow:window_->buffer->width_ * 4
                        bitsPerPixel:32] autorelease];

    NSImage *image = [[[NSImage alloc] init] autorelease];
    [image addRepresentation:image_rep];
    [image drawInRect:rect];
}

- (void)keyDown:(NSEvent *)event {
//    NSString* chars = [event characters];

    [self interpretKeyEvents:[NSArray arrayWithObject:event]];

//    NSLog(@"%d", [event keyCode]);
}

- (void)keyUp:(NSEvent *)event {
    (void)event;
}

- (void)mouseDown:(NSEvent *)event {
    (void)event;
}

- (void)mouseUp:(NSEvent *)event {
    (void)event;
}

@end

// public window class implementation
Application::Application(const char* title, uint16_t width, uint16_t height)
    /*: width_(width)
    , height_(height)*/ {
    std::cout << "Application launching...\n";

    if (NSApp == nil) {
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

        CreateWindowImpl(title, width, height);
    }
}

Application::~Application () {
    CloseWindowImpl();

    std::cout << "Application closing...\n";
}

Framebuffer* Application::GetFrameBuffer() const {
    return window_impl->buffer;
}

// window implementation
void Application::CreateWindowImpl(const char* title, uint16_t width, uint16_t height) {
    if (window_impl == nullptr) {
        window_impl = new WindowImpl();
    } else {
        // i think right now we already have window, so just do nothing
        return;
    }

    if (window_impl->buffer == nullptr) {
        window_impl->buffer = new Framebuffer();
        if (window_impl->buffer != nullptr) {
            window_impl->buffer->width_ = width;
            window_impl->buffer->height_ = height;
            window_impl->buffer->data_ = new uint32_t[width * height];
        }
    }

    NSRect rect = NSMakeRect(0, 0, width, height);

    NSUInteger mask = NSWindowStyleMaskTitled
                    | NSWindowStyleMaskClosable
                    | NSWindowStyleMaskMiniaturizable;
//                    | NSWindowStyleMaskResizable;

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

void Application::CloseWindowImpl() {
    [window_impl->handler orderOut:nil];

    [[window_impl->handler delegate] release];
    [window_impl->handler close];

    // [g_autoreleasepool drain];
    // g_autoreleasepool = [[NSAutoreleasePool alloc] init];

    delete window_impl->buffer->data_;
    delete window_impl->buffer;
    delete window_impl;
}

void Application::PresentBuffer() {
    [[window_impl->handler contentView] setNeedsDisplay:YES];
}

void Application::HandleEvent() {
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

bool Application::IsRunning() {
    return !window_impl->should_close;
}
