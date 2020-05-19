#include "engine.h"
#include <cstdint>
#include <chrono>
#include <thread>

#include <iostream>


void Engine::Run() {
    uint16_t time = 0;
    int fps = 0;

    bool bRunning = true;
    while (bRunning) {
        auto start = std::chrono::high_resolution_clock::now();

        // actual jos is here
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        auto finish = std::chrono::high_resolution_clock::now();

        time += std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
        fps++;

        if (time > 1000) {
            std::cout << fps << " frames per second;\n";
            time -= 1000;
            fps = 0;
        }
    }


}

void Engine::Stop() {
    //
}

void Engine::Tick(float dt) {
    //
}

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
