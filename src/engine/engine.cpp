#include "engine.h"

#include <chrono>
#include <thread>

#include "framebuffer.h"
#include "application.h"
#include "scenes/race_scene.h"

#include <iostream>

const uint16_t kWidth = 640;
const uint16_t kHeight = 480;

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
    uint16_t time = 0;
    int fps = 0;

    Framebuffer* framebuffer = new Framebuffer(kWidth, kHeight);
    RaceScene* scene = new RaceScene(*framebuffer);

    auto start = std::chrono::steady_clock::now();
    while (application->is_running()) {

        auto finish = std::chrono::steady_clock::now();
        double delta_time = std::chrono::duration<double>(finish - start).count();

        scene->update(delta_time);
        application->draw_buffer(framebuffer);

        time += std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
        fps++;

        if (time > 1000) {
            time -= 1000;
            fps = 0;
        }

        application->handle_event();

        start = finish;
    }

    application->close_window();

    delete scene;
    delete framebuffer;
}
