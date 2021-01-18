#include "engine.h"
#include "application.h"
#include "renderer.h"

#include <chrono>
#include <thread>

// #include "framebuffer.h"
// #include "scenes/race_scene.h"


const uint16_t kWidth = 800;
const uint16_t kHeight = 600;
const uint16_t kFPS = 60;


Engine::Engine() {
    application_ = new Application(kWidth, kHeight);
    renderer_ = new Renderer(kWidth, kHeight);
}

Engine::~Engine() {
    delete renderer_;
    delete application_;
}

void Engine::Start() {
    application_->create_window("Sanbox");

    RunLoop();
}

void Engine::RunLoop() {
    // RaceScene* scene = new RaceScene(*framebuffer);

    double dt = 1.0f / kFPS;
    auto current_time = std::chrono::steady_clock::now();

    while (application_->is_running()) {

        // scene->update(dt);

        application_->handle_event();
        application_->draw_buffer(renderer_->GetFramebuffer());

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

    application_->close_window();

    // delete scene;
}
