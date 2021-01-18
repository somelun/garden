#pragma once

class Engine {
public:
    Engine();
    ~Engine();

    void Start();
private:
    void RunLoop();

    class Application* application_;
    class Renderer* renderer_;
};
