#import <Cocoa/Cocoa.h>
#include "../shared/types.h"

@interface CocoaWindow : NSObject <NSWindowDelegate>
@property (nonatomic, readonly) NSWindow* nsWindow;
@property (nonatomic, readonly) Framebuffer* framebuffer;
@property (nonatomic, assign) BOOL shouldClose;

- (instancetype)initWithTitle:(const char*)title width:(u16)width height:(u16)height;
- (void)present;
@end
