#include <cstdint>
#include "../engine/buffer.h"

class Application {
public:
    Application();
    ~Application();

    void createWindow(const char* title, uint16_t width, uint16_t height);

    void test_update();

    void handle_event();

    Buffer* getBuffer();

private:
    class window_impl_t* window_impl{nullptr};

};
