#include "race_scene.h"
#include "../renderer.h"

// #include <math.h>
#include <iostream>

#include "../object.h"
#include "../camera.h"


Object* object;

mat4 orthographic;
mat4 perspective;

namespace defaults {
    float segment_length = 200.0f;
    uint16_t road_height = 300;
    uint16_t speed = 200;

    uint16_t drawDistance = 250;
}
// http://www.songho.ca/opengl/gl_camera.html

int roadW = 2000;
int segL = 200;
float camD = 0.84f;

struct Line {
    float x, y, z;
    float X, Y, W;

    float scale;

    Line() {
        x = y = z = 0;
    }

    void project(int camX, int camY, int camZ) {
        scale = camD / (z - camZ);
        X = (1 + scale * (x - camX)) * 640 / 2;
        Y = (1 - scale * (y - camY)) * 480 / 2;
        W = scale * roadW * 640 / 2;
    }
};


std::vector<Line> lines;

// TODO: move all constans from here later
const Color WHITE        = {255, 255, 255, 255};
const Color GREEN        = {  0, 255,   0, 255};
const Color DARK_GREEN   = { 48, 143,  56, 255};
const Color RED          = {255,   0,   0, 255};
const Color BLUE         = {  37,101, 121, 255};
const Color GREY         = {128, 128, 128, 255};


RaceScene::RaceScene(Renderer& renderer) : renderer_(renderer) {
    renderer_.FillScreen(BLUE);

    object = new Object(8);
    object->addVertex({0, 0, 0}, 0);
    object->addVertex({0, 1, 0}, 1);
    object->addVertex({1, 1, 0}, 2);
    object->addVertex({1, 0, 0}, 3);
    object->addVertex({1, 0, 1}, 4);
    object->addVertex({1, 1, 1}, 5);
    object->addVertex({0, 1, 1}, 6);
    object->addVertex({0, 0, 1}, 7);


    float near = 0.001f, far = 100.0f;
    float left = 0.0f, right = 800.0f, bottom = 600.0f, top = 0.0f;
    // 
    orthographic.at(0, 0) = 2.0f / (right - left);
    orthographic.at(1, 1) = 2.0f / (top - bottom);
    orthographic.at(2, 2) = -2.0f / (far - near);
    orthographic.at(3, 3) = 1.0f;
    orthographic.at(0, 3) = -(right + left) / (right - left);
    orthographic.at(1, 3) = -(top + bottom) / (top - bottom);
    orthographic.at(2, 3) = -(far + near) / (far - near);
    
     float angleOfView = 45.0;
     float aspectRatio = 0.75;
    
     float size = near * tanf(degreesToRadians(angleOfView) / 2.0f);
     left = -size, right = size, bottom = -size / aspectRatio, top = size / aspectRatio;
    
     perspective.at(0, 0) = 2.0f * near / (right - left);

     perspective.at(1, 1) = 2.0f * near / (top - bottom);
    
     perspective.at(0, 2) = (right + left) / (right - left);
     perspective.at(1, 2) = (top + bottom) / (top - bottom);
     perspective.at(2, 2) = -(far + near) / (far - near);
     perspective.at(3, 2) = -1.0f;
    
     perspective.at(2, 3) = -(2.0f * far * near) / (far - near);
    

    // float far = 1000.0f;
    // float near = 0.1f;
    // float fov = 90.0f;
    // float aspectRatio = (top - bottom) / (right - left);
    // float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);
    // 
    // mat4 projection;
    // projection.at(0, 0) = aspectRatio * fovRad;
    // projection.at(1, 1) = fovRad;
    // projection.at(2, 2) = far / (far - near);
    // projection.at(3, 2) = (-far * near) / (far - near);
    // projection.at(2, 3) = 1.0f;
    // projection.at(3, 3) = 0.0f;
    // projection.transpose();


    // static float angle = 30.0f;
    // vec4f* verticesRotated = new vec4f[8];
    vec4f* verticesProjected = new vec4f[8];
    // mat4 rotationMatrix = mat4_rotate_x(angle);
    // std::cout << rotationMatrix << std::endl;
    for (int i = 0; i < 3; ++i) {
        vec4f vert = {object->getVertex(i), 1.0f};
         std::cout << vert << std::endl;
        //verticesRotated[i] = rotationMatrix * vert;

        //std::cout << verticesRotated[i] << std::endl;

        verticesProjected[i] = orthographic * vert;
//        verticesProjected[i] = vert;

        // if (verticesProjected[i].w != 0.0f) {
        //     verticesProjected[i].x /= verticesProjected[i].w;
        //     verticesProjected[i].y /= verticesProjected[i].w;
        //     verticesProjected[i].z /= verticesProjected[i].w;
        // }

        // std::cout << verticesProjected[i].x << ", " << verticesProjected[i].y << std::endl;

//        verticesProjected[i].x += 1.0f;
//        verticesProjected[i].y += 1.0f;
//
//        verticesProjected[i].x *= 0.5f * 800.0f;
//        verticesProjected[i].y *= 0.5f * 600.0f;

         std::cout << verticesProjected[i] << std::endl;
        std::cout << "..................." << std::endl;

//        renderer_.DrawPixel(WHITE, verticesProjected[i].x, verticesProjected[i].y);
    }
    
//    renderer_.DrawLine(WHITE, verticesProjected[0].x, verticesProjected[0].y, verticesProjected[1].x, verticesProjected[1].y);
//    renderer_.DrawLine(WHITE, verticesProjected[1].x, verticesProjected[1].y, verticesProjected[2].x, verticesProjected[2].y);
//    renderer_.DrawLine(WHITE, verticesProjected[2].x, verticesProjected[2].y, verticesProjected[0].x, verticesProjected[0].y);
    

    
    
    mat4 M = {
        0.718762f, 0.615033f, -0.324214f, 0.0f,
        -0.393732f, 0.744416f, 0.539277f, 0.0f,
        0.573024f, -0.259959f, 0.777216f, 0.0f,
        0.526967f, 1.254234f, -2.532150f, 1.0f
    };
//    M = M.transpose();
    
    M = M.inverse();
    
    std::cout << M << std::endl;
    
//    vec4f point = {-0.5, 0.5f, -0.5f, 1.0f};
//
//    vec4f new_point = M * point;
//
//    std::cout << new_point << std::endl;

    // std::cout << trr << std::endl;
    //
    //
    //
    // vec4f asd = vec4f({12, 23, 34}, 1);
    // std::cout << mat4_identity() << std::endl;

    // mat4 test = mat4_test();

    // std::cout << test << std::endl;

    // mat4 resu =  test * test;

    // std::cout << resu << std::endl;

    // vec4f vvv = {5, 5, 5, 5};

    // vec4f weee = iden * vvv;

    // std::cout << weee << std::endl;

//     width_ = buffer_.get_width();
//     height_ = buffer_.get_height();

//     road_.reserve(500);
//     for (int i = 0; i < 500; ++i) {
//         RoadSegment* roadSegment = new RoadSegment();
//         roadSegment->n = i;
//         roadSegment->worldPoint1 = vector3i(0, 0, i * defaults::segment_length);
//         roadSegment->worldPoint2 = vector3i(0, 0, (i + 1) * defaults::segment_length);
//         roadSegment->color = DARK_GREEN;
// //        color: Math.floor(n/rumbleLength)%2 ? COLORS.DARK : COLORS.LIGHT
//         road_.push_back(roadSegment);
//     }

//     length_ = 500 * defaults::segment_length;
// //    std::cout << length_ << std::endl;


//     for (int i = 0; i < 1600; ++i) {
//         Line line;
//         line.z = i * segL;

//         lines.push_back(line);
//     }

    // uint16_t fov_angle = 60;
    // float y_world = sin(fov_angle / 2);
    // float z_world = (fov_angle / 2);

    // draw_quad(buffer, RED, {320, 100}, 100, {320, 300}, 300);
    // renderer_.DrawQuad(RED, {320, 100}, 100, {320, 300}, 300);
    // x_screen = (y_world*scaling)/z_world + (x_resolution/2)
    // 640 = (sin(30)*scaling/cos(30)) + 320
    // 320 = tan(30)*scaling
    // 320/tan(30) = scaling

    // DrawTriangle2D(buffer_, RED, {40, 40}, {30, 30}, {50, 50});

    // DrawTriagnleTop(buffer_, GREY, {300, 300}, {500, 300}, {320, 400});

    // DrawTriangleBottom(buffer_, GREY, {200, 100}, {100, 200}, {300, 200});

    // renderer_.DrawQuad(RED, {200, 200}, {400, 200}, {100, 400}, {500, 400});

    // DrawTriangle2D(buffer_, GREEN, {234, 321}, {532, 12}, {34, 444});
    // float scaling = (width_ / 2.0f) / tan(fov_angle / 2.0f);

    // track_data_.push_back(std::make_pair(0.0f, 10.0f));
    // track_data_.push_back(std::make_pair(0.2f, 200.0f));
    // track_data_.push_back(std::make_pair(0.2f, 200.0f));
    // track_data_.push_back(std::make_pair(0.2f, 200.0f));
    // track_data_.push_back(std::make_pair(0.4f, 200.0f));
    // track_data_.push_back(std::make_pair(0.4f, 200.0f));
    // track_data_.push_back(std::make_pair(0.0f, 200.0f));
    // track_data_.push_back(std::make_pair(0.0f, 200.0f));

    // track_data_.push_back(std::make_pair(1.0f, 200.0f));
    // track_data_.push_back(std::make_pair(0.0f, 400.0f));
    // track_data_.push_back(std::make_pair(-1.0f, 100.0f));
    // track_data_.push_back(std::make_pair(0.0f, 200.0f));
    // track_data_.push_back(std::make_pair(-1.0f, 200.0f));
    // track_data_.push_back(std::make_pair(1.0f, 200.0f));

    // std::vector<vector2i> vertices;
    // vertices.push_back({120, 120});
    // vertices.push_back({120, 180});
    // vertices.push_back({180, 220});
    // vertices.push_back({300, 120});
    // vertices.push_back({300, 180});
    // vertices.push_back({240, 120});
}

// current_x = 160 // Half of a 320 width screen
// dx = 0 // Curve amount, constant per segment
// ddx = 0 // Curve amount, changes per line

// for each line of the screen from the bottom to the top:
//   if line of screen's Z Map position is below segment.position:
//     dx = bottom_segment.dx
//   else if line of screen's Z Map position is above segment.position:
//     dx = segment.dx
//   end if
//   ddx += dx
//   current_x += ddx
//   this_line.x = current_x
// end for

// // Move segments
// segment_y += constant * speed // Constant makes sure the segment doesn't move too fast
// if segment.position < 0 // 0 is nearest
//   bottom_segment = segment
//   segment.position = zmap.length - 1 // Send segment position to farthest distance
//   segment.dx = GetNextDxFromTrack() // Fetch next curve amount from track data
// end if

void RaceScene::update(double dt) {
    return;
    static float angle = 1.0f;
    vec4f* verticesRotated = new vec4f[8];
    vec4f* verticesProjected = new vec4f[8];
    mat4 rotationMatrix = mat4_rotate_x(angle);
    for (int i = 0; i < 8; ++i) {
        vec4f vert = {object->getVertex(i), 1.0f};
        verticesRotated[i] = rotationMatrix * vert;
        verticesProjected[i] = orthographic * verticesRotated[i];
    }

        // renderer_.DrawPixel(WHITE, verticesProjected[i].x, verticesProjected[i].y);
    angle++;


    // void DrawLine(const Color& color, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
    return;

    distance_ += dt * defaults::speed;

//    std::cout << distance_ << std::endl;

//    RoadSegment* segment = findSegment();

    // for (int i = 1; i < 300; ++i) {
    //     Line& l = lines[i % 1600];
    //     l.project(0, 1500, 0);

    //     Color grass = (i / 3) % 2 ? Color(16, 200, 16, 255) : Color(0, 154, 0, 255);
    //     Color rumble = (i / 3) % 2 ? Color(255, 255, 255, 255) : Color(0, 0, 0, 255);
    //     Color road = (i / 3) % 2 ? Color(107, 107, 107, 255) : Color(105, 105, 105, 255);

    //     Line& p = lines[(i - 1) % 1600];

    //     // DrawQuad(buffer_, grass, {0, 0}, {0, 0}, {0, 0}, {0, 0});
    //     // DrawQuad(buffer_, rumble, {0, 0}, {0, 0}, {0, 0}, {0, 0});
    //     // DrawQuad(buffer_, road, {0, 0}, {0, 0}, {0, 0}, {0, 0});
    // }

    return;
    // return;
    // // update2(dt);
    // // return;
    //
    // static float asd = 0.1f;

//    distance_ += defaults::speed * dt * 0.5f;

    // size_t initial_y = height_ - defaults::road_height;

//    for (size_t y = height_ / 2; y < height_; ++y) {
//        for (int x = 0; x < width_; ++x) {

            // float perspective = (float)(y - height_ / 2) / height_;

//            float middle_point = 0.5f;

            // should be between 0 and 0.5
//            float half_road_width = 0.4f;// + perspective * 0.85f;
//            float clip_width = half_road_width * 0.15f;

//            int left_grass = (middle_point - half_road_width - clip_width) * width_;
//            int left_clip = (middle_point - half_road_width) * width_;
//            int right_clip = (middle_point + half_road_width) * width_;
//            int right_grass = (middle_point + half_road_width + clip_width) * width_;

            // if (x >= 0 && x < left_grass) {
            //     draw_pixel(buffer_, x, y, DARK_GREEN);
            // } else
            // if (x >= left_grass && x < left_clip) {
            //     draw_pixel(buffer_, x, y, RED);
            // }
            // else
            // if (x >= left_clip && x < right_clip) {
            //     draw_pixel(buffer_, x, y, GREY);
            // }
            // else
            // if (x >= right_clip && x <= right_grass) {
            //     draw_pixel(buffer_, x, y, RED);
            // }
            // else
            // if (x >= right_grass && x < width_) {
            //     draw_pixel(buffer_, x, y, DARK_GREEN);
            // }

            // draw_pixel(buffer_, x, y, DARK_GREEN);
//        }
//    }

    // if (asd < 10) {
    //     asd += dt;
    // }

}

void RaceScene::update2(double dt) {
    (void)dt;

//    distance_ += 100.0f * dt;
//
//    float offset = 0.0f;
//    size_t track_section = 0;
//
//    while (track_section < track_data_.size() && offset < distance_) {
//        offset += track_data_[track_section++].second;
//    }
//
//    float curv = track_data_[track_section - 1].first;
//
//    float curv_diff = (curv - curvature_) * dt;
//    curvature_ += curv_diff;
//
//    for (size_t y = height_ / 2; y < height_; ++y) {
//        for (int x = 0; x < width_; ++x) {
//
//            float perspective = (float)(y - height_ / 2) / height_;
//
//            float middle_point = 0.5f + curvature_ * powf((1.0f - perspective), 2);
//
//            float road_width = 0.05f + perspective * 0.85f;
//            float clip_width = road_width * 0.15f;
//
//            int left_grass = (middle_point - road_width - clip_width) * width_;
//            int left_clip = (middle_point - road_width) * width_;
//            int right_clip = (middle_point + road_width) * width_;
//            int right_grass = (middle_point + road_width + clip_width) * width_;
//
//            Color grass_color = sinf(28.0f * powf(1.0f - perspective, 8) + distance_ * 0.1f) > 0.0f ? GREEN : DARK_GREEN;
//            Color clip_color = sinf(80.0f * powf(1.0f - perspective, 5) + distance_) > 0.0f ? RED : WHITE;

            // if (x >= 0 && x < left_grass) {
            //     draw_pixel(buffer_, x, y, grass_color);
            // } else
            // if (x >= left_grass && x < left_clip) {
            //     draw_pixel(buffer_, x, y, clip_color);
            // }
            // else
            // if (x >= left_clip && x < right_clip) {
            //     draw_pixel(buffer_, x, y, GREY);
            // }
            // else
            // if (x >= right_clip && x <= right_grass) {
            //     draw_pixel(buffer_, x, y, clip_color);
            // }
            // else
            // if (x >= right_grass && x < width_) {
            //     draw_pixel(buffer_, x, y, grass_color);
            // }
//        }
//    }
}

RoadSegment* RaceScene::findSegment() {
    return road_[int(distance_/defaults::segment_length) % 500];
}
