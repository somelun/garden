#pragma once


class Engine {
public:
    Engine() {}
    ~Engine() {}

    // Engine(const Engine&) = delete;
    // Engine& operator=(const Engine&) = delete;
    // Engine(Engine&&) = delete;
    // Engine& operator=(Engine&&) = delete;

    // static Engine& instance() {
    //     static Engine engine;
    //     return engine;
    // }


    void Run();
    void Stop();

    void Tick(float dt);

    // bool bFixedStep{false};
};
