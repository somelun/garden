#include "engine.h"

#include <chrono>
#include <thread>

#include "framebuffer.h"
#include "../platforms/application.h"
#include "scene/race_scene.h"


Engine::Engine() {
    application = new Application();
}

Engine::~Engine() {
    delete application;
}

void Engine::start() {
    application->create_window("test window", 800, 600);

    tick();
}

void Engine::tick() {
    uint16_t time = 0;
    int fps = 0;

    Scene* scene = new RaceScene();

    Framebuffer* framebuffer = new Framebuffer();

    while (application->is_running()) {
        auto start = std::chrono::steady_clock::now();

        // actual job is here
        // std::this_thread::sleep_for(std::chrono::milliseconds(16));

        scene->update_buffer(*framebuffer);
        application->draw_buffer(framebuffer);

        auto finish = std::chrono::steady_clock::now();

        time += std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
        fps++;

        if (time > 1000) {
            time -= 1000;
            fps = 0;
        }

        application->handle_event();
    }

    application->close_window();

    delete framebuffer;
    delete scene;
}
