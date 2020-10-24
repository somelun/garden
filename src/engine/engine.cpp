#include "engine.h"

#include <chrono>
#include <thread>

#include "framebuffer.h"
#include "application.h"
#include "scenes/race_scene.h"

#include <iostream>

const uint16_t kWidth = 640;
const uint16_t kHeight = 480;
const uint16_t kFPS = 60;

Engine::Engine() {
    application = new Application();
}

Engine::~Engine() {
    delete application;
}

void Engine::start() {
    application->create_window("test window", kWidth, kHeight);

    tick();
}

void Engine::tick() {
    Framebuffer* framebuffer = new Framebuffer(kWidth, kHeight);
    RaceScene* scene = new RaceScene(*framebuffer);

    double dt = 1.0f / kFPS;
    auto current_time = std::chrono::steady_clock::now();

    while (application->is_running()) {

        scene->update(dt);
        application->draw_buffer(framebuffer);
        application->handle_event();

        auto new_time = std::chrono::steady_clock::now();
        double delta_time = std::chrono::duration<double>(new_time - current_time).count();

        double sleep_time = dt - delta_time;
        if (sleep_time > 0.0f) {
            std::this_thread::sleep_for(std::chrono::duration<double>(sleep_time));
        } else {
            // oops
        }

        current_time = new_time;
    }

    application->close_window();

    delete scene;
    delete framebuffer;
}
