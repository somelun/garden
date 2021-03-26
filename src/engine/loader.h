#pragma once

#include "math/vec.h"
#include <fstream>

namespace Loader {

    [[maybe_unused]]
    static bool LoadObjFile(const char* filePath) {
        std::ifstream ifs(filePath, std::ifstream::in);
        std::string s;

        while (std::getline(ifs, s)) {
            if (s[0] == '#') {
                continue;
            }

            std::cout << s << "\n";
        }

        return true;
    }

}
