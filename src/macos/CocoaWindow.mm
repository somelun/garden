#import "CocoaWindow.h"

@implementation CocoaWindow {
    Framebuffer* _framebuffer;
}

- (instancetype)initWithTitle:(const char*)title
                        width:(uint16_t)width
                       height:(uint16_t)height
{
    if ((self = [super init])) {
        _shouldClose = NO;

        _framebuffer = new Framebuffer();
        _framebuffer->width_ = width;
        _framebuffer->height_ = height;
        _framebuffer->data_ = new uint32_t[width * height];

        NSRect rect = NSMakeRect(0, 0, width, height);
        _nsWindow = [[NSWindow alloc] initWithContentRect:rect
                                                styleMask:(NSWindowStyleMaskTitled |
                                                           NSWindowStyleMaskClosable |
                                                           NSWindowStyleMaskMiniaturizable)
                                                  backing:NSBackingStoreBuffered
                                                    defer:NO];
        [_nsWindow setTitle:[NSString stringWithUTF8String:title]];
        [_nsWindow setDelegate:self];

        // create custom view for framebuffer display
        NSView* view = [[NSView alloc] initWithFrame:rect];
        [view setWantsLayer:YES];
        [_nsWindow setContentView:view];
        [_nsWindow makeKeyAndOrderFront:nil];
    }
    return self;
}

- (Framebuffer*)framebuffer {
    return _framebuffer;
}

- (void)present {
    if (!_framebuffer) {
        return;
    }

    NSView* view = [_nsWindow contentView];
    [view lockFocus];

    uint32_t* data = _framebuffer->data_;
    if (data) {
        NSBitmapImageRep* rep = [[NSBitmapImageRep alloc]
            initWithBitmapDataPlanes:(unsigned char**)&data
                          pixelsWide:_framebuffer->width_
                          pixelsHigh:_framebuffer->height_
                       bitsPerSample:8
                     samplesPerPixel:4
                            hasAlpha:YES
                            isPlanar:NO
                      colorSpaceName:NSDeviceRGBColorSpace
                         bytesPerRow:_framebuffer->width_ * 4
                        bitsPerPixel:32];

        NSImage* image = [[NSImage alloc] init];
        [image addRepresentation:rep];
        [image drawInRect:[view bounds]];
        [rep release];
        [image release];
    }

    [view unlockFocus];
}

- (BOOL)windowShouldClose:(NSWindow*)sender {
    _shouldClose = YES;
    return NO;
}

- (void)dealloc {
    delete[] _framebuffer->data_;
    delete _framebuffer;
    [_nsWindow close];
    [super dealloc];
}

@end
