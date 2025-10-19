#include "application.h"
#include "renderer.h"

#include <chrono>
#include <thread> // sleep_for

#define FPS    60
#define WIDTH  800
#define HEIGHT 600

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    Application* application = new Application("garden", WIDTH, HEIGHT);
    Renderer* renderer = new Renderer();

    double dt = 1.0f / FPS;
    std::chrono::time_point current_time = std::chrono::steady_clock::now();

    Framebuffer* fb = application->GetFrameBuffer();
    renderer->SetTarget(fb);

    while (application->IsRunning()) {
        // Update(dt);

       application->HandleEvent();
       application->PresentBuffer();

       std::chrono::time_point new_time = std::chrono::steady_clock::now();
       double delta_time = std::chrono::duration<double>(new_time - current_time).count();

       double sleep_time = dt - delta_time;
       if (sleep_time > 0.0f) {
           std::this_thread::sleep_for(std::chrono::duration<double>(sleep_time));
       } else {
           // TODO: handle this sad situation
       }

       current_time = new_time;
    }


    delete renderer;
    delete application;

    return 0;
}
