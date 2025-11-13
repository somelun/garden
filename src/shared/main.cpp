#include "application.h"
#include "renderer.h"
#include "mesh.h"

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

    renderer->FillScreen({122, 67, 113, 255});

    // for (u32 i = 0; i < (1<<20); ++i) {
    //     float ax = rand() % WIDTH, ay = rand() % HEIGHT;
    //     float bx = rand() % WIDTH, by = rand() % HEIGHT;
    //     renderer->DrawLine({ax, ay}, {bx, by}, { (u8)(rand() % 255), (u8)(rand() % 255), (u8)(rand() % 255), (u8)(rand() % 255) });
    // }

    const Mesh* mesh = new Mesh("../assets/teapot.obj");
    renderer->DrawMesh(mesh);

    // renderer->DrawTriangle({7, 45}, {35, 100}, {45, 60}, RED);
    // renderer->DrawTriangle({120, 35}, {90, 5}, {45, 110}, GREEN);
    // renderer->DrawTriangle({115, 83}, {80, 90}, {85, 120}, BLUE);
    // 
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

    delete mesh;
    delete renderer;
    delete application;

    return 0;
}
