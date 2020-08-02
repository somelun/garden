#pragma once

#include "../buffer.h"

/*
    This class should be a base class for any scene, this class should fill existed buffer.
    But for now just any draw code here.
    Also function names are temporary, all will be renamed!
*/
class BaseScene {
    // virtual void fill_buffer(class Buffer& buffer) = 0;

public:
    void fill_buffer(Buffer& buffer);
};
