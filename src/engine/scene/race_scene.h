#pragma once

#include "base_scene.h"

class RaceScene : public Scene
{
    virtual void update_buffer(class Framebuffer& buffer) override;

    virtual ~RaceScene() = default;
};
