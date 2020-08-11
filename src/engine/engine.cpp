#include "engine.h"
#include "../platforms/application.h"
#include <chrono>
#include "scene/race_scene.h"
#include "framebuffer.h"


// TODO: remove these later please
#include <thread>
#include <iostream>


Engine::Engine() {
    application = new Application();
}

Engine::~Engine() {
    delete application;
}

void Engine::start() {
    application->createWindow("simple window", 800, 600);

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

    application->closeWindow();
    delete scene;
}


// i create scene, scene can fill the buffer, so I should delegate all job to scene, right?

// double lastTime = getCurrentTime();
// while (true)
// {
//   double current = getCurrentTime();
//   double elapsed = current - lastTime;
//   processInput();
//   update(elapsed);
//   render();
//   lastTime = current;
// }



// double previous = getCurrentTime();
// double lag = 0.0;
// while (true)
// {
//   double current = getCurrentTime();
//   double elapsed = current - previous;
//   previous = current;
//   lag += elapsed;

//   processInput();

//   while (lag >= MS_PER_UPDATE)
//   {
//     update();
//     lag -= MS_PER_UPDATE;
//   }

//   render();
// }




    // double t = 0.0;
    // double dt = 0.01;

    // double currentTime = hires_time_in_seconds();
    // double accumulator = 0.0;

    // State previous;
    // State current;

    // while ( !quit )
    // {
    //     double newTime = time();
    //     double frameTime = newTime - currentTime;
    //     if ( frameTime > 0.25 )
    //         frameTime = 0.25;
    //     currentTime = newTime;

    //     accumulator += frameTime;

    //     while ( accumulator >= dt )
    //     {
    //         previousState = currentState;
    //         integrate( currentState, t, dt );
    //         t += dt;
    //         accumulator -= dt;
    //     }

    //     const double alpha = accumulator / dt;

    //     State state = currentState * alpha +
    //         previousState * ( 1.0 - alpha );

    //     render( state );
    // }
