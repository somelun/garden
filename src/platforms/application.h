#include <cstdint>

class Application {
public:
    Application();
    ~Application();

    void createWindow(const char* title, uint16_t width, uint16_t height);

    void handle_event();

private:
    class window_impl_t* window_impl{nullptr};

};
