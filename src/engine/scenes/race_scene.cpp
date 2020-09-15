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
    // fill(buffer_, WHITE);

    track_data.push_back(std::make_pair(0.0f, 10.0f));
    track_data.push_back(std::make_pair(0.0f, 200.0f));
    track_data.push_back(std::make_pair(1.0f, 200.0f));
    track_data.push_back(std::make_pair(0.0f, 400.0f));
    track_data.push_back(std::make_pair(-1.0f, 100.0f));
    track_data.push_back(std::make_pair(0.0f, 200.0f));
    track_data.push_back(std::make_pair(-1.0f, 200.0f));
    track_data.push_back(std::make_pair(1.0f, 200.0f));
}

void RaceScene::update_buffer(double delta_time) {
    uint16_t width = buffer_.get_width();
    uint16_t height = buffer_.get_height();

    distance_ += 100.0f * delta_time;

    float offset = 0.0f;
    int track_section = 0;

    while (track_section < track_data.size() && offset < distance_) {
        offset += track_data[track_section++].second;
    }

    float curv = track_data[track_section - 1].first;

    float curv_diff = (curv - curvature_) * delta_time;
    curvature_ += curv_diff;

    for (size_t y = height / 2; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            float perspective = (float)(y - height / 2) / height;

            float middle_point = 0.5f + curvature_;//0.5f * powf((1.0f - perspective), 3);

            float road_width = 0.05f + perspective * 0.85f;
            float clip_width = road_width * 0.15f;

            int left_grass = (middle_point - road_width - clip_width) * width;
            int left_clip = (middle_point - road_width) * width;
            int right_clip = (middle_point + road_width) * width;
            int right_grass = (middle_point + road_width + clip_width) * width;

            color_t grass_color = sinf(28.0f * powf(1.0f - perspective, 3) + distance_ * 0.1f) > 0.0f ? GREEN : DARK_GREEN;
            color_t clip_color = sinf(80.0f * powf(1.0f - perspective, 3) + distance_) > 0.0f ? RED : WHITE;

            if (x >= 0 && x < left_grass) {
                draw_pixel(buffer_, x, y, grass_color);
            } else
            if (x >= left_grass && x < left_clip) {
                draw_pixel(buffer_, x, y, clip_color);
            }
            else
            if (x >= left_clip && x < right_clip) {
                draw_pixel(buffer_, x, y, GREY);
            }
            else
            if (x >= right_clip && x <= right_grass) {
                draw_pixel(buffer_, x, y, clip_color);
            }
            else
            if (x >= right_grass && x < width) {
                draw_pixel(buffer_, x, y, grass_color);
            }
        }
    }
    // abort();
}
