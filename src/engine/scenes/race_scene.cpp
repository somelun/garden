#include "race_scene.h"
#include "../render2d.h"

#include <math.h>

#include <iostream>

const uint16_t kRoadHeight = 300;
const uint16_t kSpeed = 100;


// TODO: move all constans from here later
const color_t WHITE        = {255, 255, 255, 255};
const color_t GREEN        = {  0, 255,   0, 255};
const color_t DARK_GREEN   = { 48, 143,  56, 255};
const color_t RED          = {255,   0,   0, 255};
const color_t BLUE         = {  37,101, 121, 255};
const color_t GREY         = {128, 128, 128, 255};


RaceScene::RaceScene(Framebuffer& buffer) : buffer_(buffer) {
    fill(buffer_, BLUE);

    width_ = buffer_.get_width();
    height_ = buffer_.get_height();

    uint16_t fov_angle = 60;
    float y_world = sin(fov_angle / 2);
    float z_world = (fov_angle / 2);

    // x_screen = (y_world*scaling)/z_world + (x_resolution/2)
    // 640 = (sin(30)*scaling/cos(30)) + 320
    // 320 = tan(30)*scaling
    // 320/tan(30) = scaling

    float scaling = (width_ / 2.0f) / tan(fov_angle / 2.0f);

    track_data_.push_back(std::make_pair(0.0f, 10.0f));
    track_data_.push_back(std::make_pair(0.2f, 200.0f));
    track_data_.push_back(std::make_pair(0.2f, 200.0f));
    track_data_.push_back(std::make_pair(0.2f, 200.0f));
    track_data_.push_back(std::make_pair(0.4f, 200.0f));
    track_data_.push_back(std::make_pair(0.4f, 200.0f));
    track_data_.push_back(std::make_pair(0.0f, 200.0f));
    track_data_.push_back(std::make_pair(0.0f, 200.0f));
    // track_data_.push_back(std::make_pair(1.0f, 200.0f));
    // track_data_.push_back(std::make_pair(0.0f, 400.0f));
    // track_data_.push_back(std::make_pair(-1.0f, 100.0f));
    // track_data_.push_back(std::make_pair(0.0f, 200.0f));
    // track_data_.push_back(std::make_pair(-1.0f, 200.0f));
    // track_data_.push_back(std::make_pair(1.0f, 200.0f));
}

void RaceScene::update(double dt) {
    // update2(dt);
    // return;

    distance_ += kSpeed * dt;

    size_t initial_y = height_ - kRoadHeight;

    for (size_t y = height_ / 2; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {

            float perspective = (float)(y - height_ / 2) / height_;

            float middle_point = 0.5f;

            float road_width = 0.05f + perspective * 0.85f;
            float clip_width = road_width * 0.15f;

            int left_grass = (middle_point - road_width - clip_width) * width_;
            int left_clip = (middle_point - road_width) * width_;
            int right_clip = (middle_point + road_width) * width_;
            int right_grass = (middle_point + road_width + clip_width) * width_;

            if (x >= 0 && x < left_grass) {
                draw_pixel(buffer_, x, y, DARK_GREEN);
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
            if (x >= right_grass && x < width_) {
                draw_pixel(buffer_, x, y, DARK_GREEN);
            }

            // draw_pixel(buffer_, x, y, DARK_GREEN);
        }
    }
}

void RaceScene::update2(double dt) {
    distance_ += 100.0f * dt;

    float offset = 0.0f;
    size_t track_section = 0;

    while (track_section < track_data_.size() && offset < distance_) {
        offset += track_data_[track_section++].second;
    }

    float curv = track_data_[track_section - 1].first;

    float curv_diff = (curv - curvature_) * dt;
    curvature_ += curv_diff;

    for (size_t y = height_ / 2; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {

            float perspective = (float)(y - height_ / 2) / height_;

            float middle_point = 0.5f + curvature_ * powf((1.0f - perspective), 2);

            float road_width = 0.05f + perspective * 0.85f;
            float clip_width = road_width * 0.15f;

            int left_grass = (middle_point - road_width - clip_width) * width_;
            int left_clip = (middle_point - road_width) * width_;
            int right_clip = (middle_point + road_width) * width_;
            int right_grass = (middle_point + road_width + clip_width) * width_;

            color_t grass_color = sinf(28.0f * powf(1.0f - perspective, 8) + distance_ * 0.1f) > 0.0f ? GREEN : DARK_GREEN;
            color_t clip_color = sinf(80.0f * powf(1.0f - perspective, 5) + distance_) > 0.0f ? RED : WHITE;

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
            if (x >= right_grass && x < width_) {
                draw_pixel(buffer_, x, y, grass_color);
            }
        }
    }
}
