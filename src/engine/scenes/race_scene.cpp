#include "race_scene.h"
#include "../render2d.h"

void RaceScene::update_buffer(Framebuffer& buffer) {
    draw_line(buffer, 0, 0, 400, 400);
}
