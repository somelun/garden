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

    Framebuffer* fb = application->GetFrameBuffer();
    renderer->SetTarget(fb);

    double target_time = 1.0f / FPS;
    std::chrono::time_point last_time = std::chrono::steady_clock::now();
    while (application->IsRunning()) {
        application->HandleEvent();

        std::chrono::time_point now = std::chrono::steady_clock::now();
        double delta_time = std::chrono::duration<double>(now - last_time).count();
        last_time = now;

        // scene->Update(delta_time);
        // renderer->Render(scene);

        application->PresentBuffer();

        std::chrono::time_point end = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double>(end - now).count();
        double sleep_time = target_time - elapsed;

        if (sleep_time > 0.0f) {
            std::this_thread::sleep_for(std::chrono::duration<double>(sleep_time));
        }
    }

    delete renderer;
    delete application;

    return 0;
}
