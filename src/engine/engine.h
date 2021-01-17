#pragma once

class Engine {
public:
    Engine();
    ~Engine();

    void start();
private:
    void RunLoop();

    class Application* application;
};
