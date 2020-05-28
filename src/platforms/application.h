#include <cstdint>

class Application {
public:
    Application(); //NSApp created here
    ~Application();

    void run();

    void createWindow(const char* title, uint16_t width, uint16_t height);
private:
    //
};
