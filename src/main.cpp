// #include "platforms/application.h"

#include "engine/engine.h"

#include <iostream>

int main(int argc, char *argv[]) {
    Engine engine;
    engine.start();

    return 0;
}


// g++ test.mm -framework Cocoa
// mkdir -p cli.app/Contents/MacOS
// cp a.out cli.app/Contents/MacOS/cli
// and then run cli.app/Contents/MacOS/cli from the command line,
// your process will show up as a running application.


// engine
// in constructor we create application, render and all other what we need
// if all good, we can run loop and also before the loop we can check how many
// windows do we have right now. if less then 1, then we create one window and
// run loop for this window. sounds good?