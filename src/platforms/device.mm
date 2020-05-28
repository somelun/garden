#include <Cocoa/Cocoa.h>

#include "device.h"

#include <iostream>

@interface MacViewItfc : NSView
-(void)drawRect:(NSRect)rect;
@end

@implementation MacViewItfc
-(void) drawRect:(NSRect)rect {
  [[NSColor grayColor] set];
  NSRectFill([self bounds]);

  std::cout << "Draw\n";
}
@end

@interface MacWindowItfc : NSWindow <NSApplicationDelegate>
@end

@implementation MacWindowItfc
@end

namespace Outlaw {
  //C++ Wrapper for ViewItfc (NSView)
  struct MacViewImpl {
    MacViewItfc* pimpl;
  };
  struct MacViewRect {
    NSRect pimpl = NSMakeRect(100.0,100.0,300.0,300.0);
  };
  MacView::MacView() :
    impl(new MacViewImpl), frame(new MacViewRect) {
    impl->pimpl = [[MacViewItfc alloc] initWithFrame:frame->pimpl];
  }
  MacView::~MacView() {
    if (impl)
      [impl->pimpl release];
  }

  //C++ Wrapper for WindowItfc (NSWindow)
  struct MacWindowImpl {
    MacWindowItfc* pimpl;
  };
  MacWindow::MacWindow(MacView* view) :
    impl(new MacWindowImpl) {
    impl->pimpl = [[MacWindowItfc alloc] initWithContentRect:view->frame->pimpl
                                         styleMask:NSWindowStyleMaskTitled
                                                  |NSWindowStyleMaskClosable
                                                  |NSWindowStyleMaskResizable
                                         backing:NSBackingStoreBuffered
                                         defer:NO];

    [impl->pimpl setTitle:@"Outlaw Game"];
    [impl->pimpl setContentView:view->impl->pimpl];
    [impl->pimpl makeKeyAndOrderFront:nil];
  }
  MacWindow::~MacWindow() {
    std::cout << "~MacWindow\n";
    if (impl)
      [impl->pimpl release];
  }

  //C++ Wrapper for NSApplication
  struct MacDeviceImpl {
    NSApplication* pimpl;
  };
  MacDevice::MacDevice()
    : impl(new MacDeviceImpl) {
      impl->pimpl = [NSApplication sharedApplication];
      view = new MacView();
      window = new MacWindow(view);
      [impl->pimpl setDelegate:window->impl->pimpl];
  }
  MacDevice::~MacDevice() {
    std::cout << "~MacDevice\n";
    if (impl)
      [impl->pimpl release];
  }
  void MacDevice::Run() {
    std::cout << "Run\n";
    [impl->pimpl run];
  }
}