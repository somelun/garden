#pragma once

/**
 * This class should be a base class for any scene, this class should fill existed buffer.
 * But for now just any draw code here.
 */
class Scene {
public:
    virtual void update_buffer(class Framebuffer& buffer) = 0;

    virtual ~Scene() = default;
};
