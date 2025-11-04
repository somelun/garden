#import "cocoa_window.h"

///////////////////////////

@interface FramebufferView : NSView
- (instancetype)initWithFramebuffer:(Framebuffer*)fb;
@property (nonatomic, readonly) Framebuffer* framebuffer;
@end

@implementation FramebufferView {
    Framebuffer* _framebuffer;
}

- (instancetype)initWithFramebuffer:(Framebuffer*)fb {
    if ((self = [super initWithFrame:NSZeroRect])) {
        _framebuffer = fb;
        [self setWantsLayer:YES];
    }
    return self;
}

- (Framebuffer*)framebuffer {
    return _framebuffer;
}

- (void)drawRect:(NSRect)dirtyRect {
    if (!_framebuffer || !_framebuffer->data) {
        return;
    }

    uint32_t* data = _framebuffer->data;
    NSBitmapImageRep* rep = [[NSBitmapImageRep alloc]
        initWithBitmapDataPlanes:(unsigned char**)&data
                      pixelsWide:_framebuffer->width
                      pixelsHigh:_framebuffer->height
                   bitsPerSample:8
                 samplesPerPixel:4
                        hasAlpha:YES
                        isPlanar:NO
                  colorSpaceName:NSDeviceRGBColorSpace
                     bytesPerRow:_framebuffer->width * 4
                    bitsPerPixel:32];

    NSImage* image = [[NSImage alloc] init];
    [image addRepresentation:rep];
    [image drawInRect:[self bounds]];

    [rep release];
    [image release];
}
@end

/////////////////////////////////

@implementation CocoaWindow {
    Framebuffer* _framebuffer;
    FramebufferView* _view;
}

- (instancetype)initWithTitle:(const char*)title
                        width:(u16)width
                       height:(u16)height
{
    if ((self = [super init])) {
        _shouldClose = NO;

        _framebuffer = new Framebuffer();
        _framebuffer->width = width;
        _framebuffer->height = height;
        _framebuffer->data = new u32[width * height];

        NSRect rect = NSMakeRect(0, 0, width, height);
        _nsWindow = [[NSWindow alloc] initWithContentRect:rect
                                                styleMask:(NSWindowStyleMaskTitled |
                                                           NSWindowStyleMaskClosable |
                                                           NSWindowStyleMaskMiniaturizable)
                                                  backing:NSBackingStoreBuffered
                                                    defer:NO];
        [_nsWindow setTitle:[NSString stringWithUTF8String:title]];
        [_nsWindow setDelegate:self];

        _view = [[FramebufferView alloc] initWithFramebuffer:_framebuffer];
        [_nsWindow setContentView:_view];
        [_nsWindow makeKeyAndOrderFront:nil];
        [_view release]; // if not using ARC
    }
    return self;
}

- (Framebuffer*)framebuffer {
    return _framebuffer;
}

- (void)present {
    [_view setNeedsDisplay:YES];
}

- (BOOL)windowShouldClose:(NSWindow*)sender {
    _shouldClose = YES;
    return NO;
}

- (void)dealloc {
    delete[] _framebuffer->data;
    delete _framebuffer;
    [_nsWindow close];
    [super dealloc];
}

@end
