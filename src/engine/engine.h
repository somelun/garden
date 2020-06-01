#pragma once

#include <iostream>
#include <vector>


class Engine {
public:
    Engine();
    ~Engine();

    void start();
private:
    void tick();

    class Application* application;
};
