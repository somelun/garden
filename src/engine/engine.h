#pragma once

#include <iostream>


class Engine {
public:
    Engine() {
        std::cout << "Engine created...\n";
    }
    ~Engine() {
        std::cout << "Engine destroyed.\n";
    }

    bool initialize();
    void terminate();

    void run();

    // bool bFixedStep{false};
};
