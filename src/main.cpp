#include <iostream>
#include "engine/engine.h"
// #include "platforms/window.h"

#include "platforms/device.h"

#include "platforms/application.h"

int main(int argc, char *argv[]) {

    std::cout << "Hollow world\n";

    Application application;
    application.createWindow("empty window", 640, 480);
    application.run();

    // Outlaw::MacDevice* device = new Outlaw::MacDevice();
    // device->Run();

    // platform_initialize();

//    bool f = engine.initialize();
//    if (f) {
//        engine.run();
//        // std::cout << "!!!!!!!!!!!!!!\n";
//    }

    return 0;
}


// g++ test.mm -framework Cocoa
// mkdir -p cli.app/Contents/MacOS
// cp a.out cli.app/Contents/MacOS/cli
// and then run cli.app/Contents/MacOS/cli from the command line, your process will show up as a running application.