#pragma once

/*
    This class should be a base class for any scene, this class should fill existed buffer.
    But for now just any draw code here.
    Also function names are temporary, all will be renamed!
*/
class Scene {
    // virtual void fill_buffer(class Buffer& buffer) = 0;

public:
    void update_buffer(class Framebuffer& buffer);
};
