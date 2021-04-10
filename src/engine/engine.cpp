#include "engine.h"
#include "application.h"
#include "renderer.h"

#include <chrono>
#include <thread>

#include "scenes/test_scene.h"


const uint16_t kWidth = 800;
const uint16_t kHeight = 600;
const uint16_t kFPS = 60;


Engine::Engine() {
    //application_ = new Application("garden", kWidth, kHeight);
    renderer_ = new Renderer(kWidth, kHeight);
}

Engine::~Engine() {
    delete renderer_;
    //delete application_;
}

void Engine::RunLoop() {
    TestScene* scene = new TestScene(*renderer_);

    double dt = 1.0f / kFPS;
    auto current_time = std::chrono::steady_clock::now();

    //while (application_->IsRunning()) {

    //    scene->Update(dt);

    //    application_->HandleEvent();
    //    application_->PresentBuffer(renderer_->GetFramebuffer());

    //    auto new_time = std::chrono::steady_clock::now();
    //    double delta_time = std::chrono::duration<double>(new_time - current_time).count();

    //    double sleep_time = dt - delta_time;
    //    if (sleep_time > 0.0f) {
    //        std::this_thread::sleep_for(std::chrono::duration<double>(sleep_time));
    //    } else {
    //        // TODO: handle this sad situation
    //    }

    //    current_time = new_time;
    //}

    delete scene;
}
