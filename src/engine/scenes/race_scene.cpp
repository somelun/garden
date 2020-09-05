#include "race_scene.h"
#include "../render2d.h"

#include <iostream>


// TODO: move all constans from here later
const color_t WHITE  = {255, 255, 255, 255};
const color_t GREEN  = {  0, 255,   0, 255};
const color_t RED    = {255,   0,   0, 255};
const color_t BLUE   = {  0,   0, 255, 255};
const color_t GREY   = {128, 128, 128, 255};


void RaceScene::update_buffer(Framebuffer& buffer) {
    fill(buffer, WHITE);

    uint16_t width = buffer.get_width();
    uint16_t height = buffer.get_height();

    // std::cout << "======================================" << std::endl;

    for (size_t y = height / 2; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            float perspective = (float)(y - height / 2) / height;

            float middle_point = 0.5f;
            float road_width = perspective;
            float clip_width = road_width * 0.15f;

            // road_width *= 0.5f;

            int left_grass = (middle_point - road_width - clip_width) * width;
            int left_clip = (middle_point - road_width) * width;
            size_t right_clip = (middle_point + road_width) * width;
            size_t right_grass = (middle_point + road_width + clip_width) * width;

            // if (y < 440) {
            //     continue;
            // }

            // std::cout << y << std::endl;

            // std::cout << left_grass << ", " << x << ", " << left_clip << std::endl;

            if (x >= 0 && x < left_grass) {
                draw_pixel(buffer, x, y, GREEN);
            } else
            if (x >= left_grass && x < left_clip) {
                draw_pixel(buffer, x, y, RED);
            }
            else
            if (x >= left_clip && x < right_clip) {
                draw_pixel(buffer, x, y, GREY);
            }
            else
            if (x >= right_clip && x <= right_grass) {
                draw_pixel(buffer, x, y, RED);
            }
            else
            if (x >= right_grass && x < width) {
                draw_pixel(buffer, x, y, GREEN);
            }
        }
    }
    // abort();
//
    // std::cout << "======================================" << std::endl;
}
