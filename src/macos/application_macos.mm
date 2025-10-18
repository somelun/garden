#include "../shared/application.h"

#import "cocoa_window.h"

Application::Application(const char* title, uint16_t width, uint16_t height) {
    if (NSApp == nil) {
        [NSApplication sharedApplication];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

        id menubar = [[NSMenu new] autorelease];
        id appMenuItem = [[NSMenuItem new] autorelease];
        [menubar addItem:appMenuItem];
        [NSApp setMainMenu:menubar];

        id appMenu = [[NSMenu new] autorelease];
        NSString* appName = [[NSProcessInfo processInfo] processName];
        NSString* quitTitle = [@"Quit " stringByAppendingString:appName];
        NSMenuItem* quitItem = [[[NSMenuItem alloc] initWithTitle:quitTitle
                                                           action:@selector(terminate:)
                                                    keyEquivalent:@"q"] autorelease];
        [appMenu addItem:quitItem];
        [appMenuItem setSubmenu:appMenu];

        [NSApp finishLaunching];
    }

    platform_window_ = [[CocoaWindow alloc] initWithTitle:title width:width height:height];
}

Application::~Application() {
    [(id)platform_window_ release];
}

Framebuffer* Application::GetFrameBuffer() const {
    return [(CocoaWindow*)platform_window_ framebuffer];
}

void Application::PresentBuffer() {
    [(CocoaWindow*)platform_window_ present];
}

void Application::HandleEvent() {
    @autoreleasepool {
        NSEvent* event;
        while ((event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                           untilDate:[NSDate dateWithTimeIntervalSinceNow:0.01]
                                              inMode:NSDefaultRunLoopMode
                                             dequeue:YES])) {
            [NSApp sendEvent:event];
        }
    }
}

bool Application::IsRunning() const {
    return ![(CocoaWindow*)platform_window_ shouldClose];
}

