#import <Cocoa/Cocoa.h>
#include "../shared/framebuffer.h"

@interface CocoaWindow : NSObject <NSWindowDelegate>
@property (nonatomic, readonly) NSWindow* nsWindow;
@property (nonatomic, readonly) Framebuffer* framebuffer;
@property (nonatomic, assign) BOOL shouldClose;

- (instancetype)initWithTitle:(const char*)title width:(uint16_t)width height:(uint16_t)height;
- (void)present;
@end
