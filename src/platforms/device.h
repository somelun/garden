namespace Outlaw {

    //C++ NSView Wrapper Class
    struct MacViewImpl;
    struct MacViewRect;
    class MacView {
    public:
      MacViewImpl* impl;
      MacViewRect* frame;
      MacView();
      ~MacView();
    };

    //C++ NSWindow Wrapper Class;
    struct MacWindowImpl;
    class MacWindow {
    public:
      MacWindowImpl* impl;
      MacWindow(MacView* view);
      ~MacWindow();
    };

    struct MacDeviceImpl;
    class MacDevice {
    public:
      MacDeviceImpl* impl;

      MacWindow* window;
      MacView* view;
      MacDevice();
      ~MacDevice();
      void Run();
    };
}