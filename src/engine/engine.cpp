#include "engine.h"
#include <cstdint>
#include <chrono>

// remove these later please
#include <thread>
#include <iostream>

// #include "../platforms/window.h"


template <typename F>
struct privDefer {
    F f;
    privDefer(F f) : f(f) {}
    ~privDefer() {
        f();
    }
};

template <typename F>
privDefer<F> defer_func(F f) {
    return privDefer<F>(f);
}

#define DEFER_1(x, y) x##y
#define DEFER_2(x, y) DEFER_1(x, y)
#define DEFER_3(x)    DEFER_2(x, __COUNTER__)
#define defer(code)   auto DEFER_3(_defer_) = defer_func([&](){code;})


// typedef void (*callback_function)(void);

// class Defer {
// public:
//     Defer(void *c) : callback(c) {}
//     ~Defer() {
//         callback();

//         std::cout << "asdfsdfdsfds\n";
//     }
// private:
//      void *callback;
// };

bool Engine::initialize() {

    // Window* window = new Window();

    // uint16_t time = 0;
    // int fps = 0;

    // bool bRunning = true;
    // while (bRunning) {
    //     auto start = std::chrono::high_resolution_clock::now();

    //     // actual job is here
    //     std::this_thread::sleep_for(std::chrono::milliseconds(1));

    //     auto finish = std::chrono::high_resolution_clock::now();

    //     time += std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    //     fps++;

    //     if (time > 1000) {
    //         std::cout << fps << " frames per second;\n";
    //         time -= 1000;
    //         fps = 0;
    //     }
    // }

    // Defer d = Defer(Engine::Tick);

    // defer(Tick());
    std::cout << "12312321321\n";


    return true;
}

void Engine::terminate() {
    //
}

void Engine::run() {
    std::cout << "tick\n";

    uint16_t time = 0;
    int fps = 0;

    bool bRunning = true;
    while (bRunning) {
        auto start = std::chrono::high_resolution_clock::now();

        // actual job is here
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
