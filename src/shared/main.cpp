#include "engine.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    Engine engine;
    engine.RunLoop();

    return 0;
}
