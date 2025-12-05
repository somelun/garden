#include "application.h"
#include "renderer.h"
#include "mesh.h"
#include "camera.h"
#include "light.h"

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

    Camera camera;
    camera.position = {0.0f, -3.0f, -7.0f};
    camera.target   = {0.0f, 0.0f, 0.0f};
    camera.fov_deg  = 70.0f;
    camera.aspect   = 1.33f;
    camera.z_near   = 0.1f;
    camera.z_far    = 100.0f;

    Light light;
    light.position  = {0.0f, 0.0f, -4.0f};
    light.color     = {255, 0, 0, 255};
    light.intensity = 1.2f;
    light.ambient   = 0.05f;
    light.diffuse   = 1.0f;
    light.specular  = 0.8f;
    light.shininess = 32.0f;

    Framebuffer* framebuffer = application->GetFrameBuffer();
    renderer->Initialize(framebuffer);

    Mesh* mesh = new Mesh();
    if (!mesh->LoadFromObjFile("../assets/teapot.obj")) {
        return 1;
    }

    float angle = 0.0f;
    double target_time = 1.0f / FPS;
    std::chrono::time_point last_time = std::chrono::steady_clock::now();
    while (application->IsRunning()) {
        application->HandleEvent();

        std::chrono::time_point now = std::chrono::steady_clock::now();
        double delta_time = std::chrono::duration<double>(now - last_time).count();
        last_time = now;

        angle += 0.5f * delta_time;   // speed in radians/sec
        float radius = 8.0f;

        camera.position.x = sin(angle) * radius;
        camera.position.z = cos(angle) * radius;
        camera.position.y = 2.0f;

        // scene->Update(delta_time);
        renderer->FillScreen({122, 67, 113, 255});
        renderer->DrawMesh(mesh, camera, light, RenderMode::Phong);

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
