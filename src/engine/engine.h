#pragma once

class Engine {
public:
    Engine();
    ~Engine();

    void RunLoop();

private:
    class Application* application_;
    class Renderer* renderer_;
};
