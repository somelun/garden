#include "race_scene.h"
#include "../render2d.h"

// TODO: move all constans from here later
const color_t WHITE  = {255, 255, 255, 255};
const color_t GREEN  = {  0, 255,   0, 255};
const color_t RED    = {255,   0,   0, 255};
const color_t BLUE   = {  0,   0, 255, 255};

void RaceScene::update_buffer(Framebuffer& buffer) {
    // draw_line(buffer, 0, 0, 400, 400, WHITE);

    // uint16_t width = buffer.get_width();
    // uint16_t height = buffer.get_height();

    // for (size_t y = 0; y < height / 2; ++y) {
    //     for (size_t x = 0; x < width; ++x) {
    //         float middle_point = 0.5f;
    //         float road_width = 0.6f;
    //         float clip_width = road_width * 0.15f;


    //     }
    // }
}
