#include "race_scene.h"
#include "../render2d.h"

#include <math.h>

#include <iostream>


// TODO: move all constans from here later
const color_t WHITE        = {255, 255, 255, 255};
const color_t GREEN        = {  0, 255,   0, 255};
const color_t DARK_GREEN   = {0, 101, 51, 255};
const color_t RED          = {255,   0,   0, 255};
const color_t BLUE         = {  0,   0, 255, 255};
const color_t GREY         = {128, 128, 128, 255};


RaceScene::RaceScene(Framebuffer& buffer) : buffer_(buffer) {
    fill(buffer_, WHITE);
}

void RaceScene::update_buffer() {
    uint16_t width = buffer_.get_width();
    uint16_t height = buffer_.get_height();

    distance_ += 10.0f * 0.1f;

    for (size_t y = height / 2; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            float perspective = (float)(y - height / 2) / height;

            float middle_point = 0.5f;
            float road_width = 0.05f + perspective * 0.85f;
            float clip_width = road_width * 0.15f;

            int left_grass = (middle_point - road_width - clip_width) * width;
            int left_clip = (middle_point - road_width) * width;
            int right_clip = (middle_point + road_width) * width;
            int right_grass = (middle_point + road_width + clip_width) * width;

            color_t grass_color = sinf(20.0f * powf(1.0f - perspective, 3) + distance_ * 0.1f) > 0.0f ? GREEN : DARK_GREEN;

            if (x >= 0 && x < left_grass) {
                draw_pixel(buffer_, x, y, grass_color);
            } else
            if (x >= left_grass && x < left_clip) {
                draw_pixel(buffer_, x, y, RED);
            }
            else
            if (x >= left_clip && x < right_clip) {
                draw_pixel(buffer_, x, y, GREY);
            }
            else
            if (x >= right_clip && x <= right_grass) {
                draw_pixel(buffer_, x, y, RED);
            }
            else
            if (x >= right_grass && x < width) {
                draw_pixel(buffer_, x, y, grass_color);
            }
        }
    }
    // abort();
}
