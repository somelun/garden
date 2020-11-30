#include "race_scene.h"
#include "../render2d.h"

#include <math.h>

#include <iostream>

#define FIXP16_SHIFT 16

namespace defaults {
    float segment_length = 200.0f;
    uint16_t road_height = 300;
    uint16_t speed = 100;
}

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


    for (int i = 0; i < 1600; ++i) {
        segments_.emplace_back(Segment());
    }
    // uint16_t fov_angle = 60;
    // float y_world = sin(fov_angle / 2);
    // float z_world = (fov_angle / 2);

    // draw_quad(buffer, RED, {320, 100}, 100, {320, 300}, 300);
    // draw_quad(buffer, RED, {320, 100}, 100, {320, 300}, 300);
    // x_screen = (y_world*scaling)/z_world + (x_resolution/2)
    // 640 = (sin(30)*scaling/cos(30)) + 320
    // 320 = tan(30)*scaling
    // 320/tan(30) = scaling

    // DrawTriangle2D(buffer_, RED, {40, 40}, {30, 30}, {50, 50});

    // DrawTriagnleTop(buffer_, GREY, {300, 300}, {500, 300}, {320, 400});

    // DrawTriangleBottom(buffer_, GREY, {200, 100}, {100, 200}, {300, 200});

    DrawTriangle2D(buffer_, GREEN, {234, 321}, {532, 12}, {34, 444});
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

    // for (int i = 0; i < 300; ++i) {
    //     Segment& segment = segments_[i % 1600];
    //     segment.project({0, 500, 0});
    //
    //     Segment p = segments_[(i - 1) % 1600];
    //
    //     draw_quad(buffer_, GREEN, {0, p.screen_coords.y}, width_, {0, segment.screen_coords.y}, width_);
        // draw_quad(buffer, RED, {320, 100}, 100, {320, 300}, 300);
    //     // draw_quad(buffer, RED, {320, 100}, 100, {320, 300}, 300);
    // }
    //


    // draw_triangle_flat_bottom(buffer_, GREY, {180, 120}, {240, 180}, {120, 180});
    //
    // draw_triangle_flat_top(buffer_, GREY, {300, 300}, {500, 300}, {400, 400});


    return;
    // return;
    // // update2(dt);
    // // return;
    //
    // static float asd = 0.1f;

    distance_ += defaults::speed * dt * 0.5f;

    // size_t initial_y = height_ - defaults::road_height;

    for (size_t y = height_ / 2; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {

            // float perspective = (float)(y - height_ / 2) / height_;

            float middle_point = 0.5f;

            // should be between 0 and 0.5
            float half_road_width = 0.4f;// + perspective * 0.85f;
            float clip_width = half_road_width * 0.15f;

            int left_grass = (middle_point - half_road_width - clip_width) * width_;
            int left_clip = (middle_point - half_road_width) * width_;
            int right_clip = (middle_point + half_road_width) * width_;
            int right_grass = (middle_point + half_road_width + clip_width) * width_;

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

    // if (asd < 10) {
    //     asd += dt;
    // }

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

void RaceScene::draw_triangle_flat_bottom(Framebuffer& buffer, const color_t& color, vector2i p0, vector2i p1, vector2i p2) {
    float dxy_left  = (p2.x - p0.x) / (p2.y - p0.y);
    float dxy_right = (p1.x - p0.x) / (p1.y - p0.y);

    float xs = p0.x;
    float xe = p0.x;

    for (int y = p0.y; y <= p1.y; ++y) {
        draw_line(buffer, xs, y, xe, y, color);

        xs += dxy_left;
        xe += dxy_right;

    }
}

void RaceScene::draw_triangle_flat_top(Framebuffer& buffer, const color_t& color, vector2i p0, vector2i p1, vector2i p2) {
    float dxy_left  = (p2.x - p0.x) / (p2.y - p0.y);
    float dxy_right = (p2.x - p1.x) / (p2.y - p1.y);

    float xs = p0.x;
    float xe = p1.x;

    for (int y = p0.y; y <= p2.y; ++y) {
        draw_line(buffer, xs, y, xe, y, color);

        xs += dxy_left;
        xe += dxy_right;

    }
}

void RaceScene::DrawTriangle2D(Framebuffer& buffer, const Color& color, Point p1, Point p2, Point p3) {
    // check for horizontal or vertical
    if ((p1.x == p2.x && p2.x == p3.x) || (p1.y == p2.y && p2.y == p3.y)) {
        return;
    }

    if (p2.y < p1.y) {
        std::swap(p1, p2);
    }

    if (p3.y < p1.y) {
        std::swap(p1, p3);
    }

    if (p3.y < p2.y) {
        std::swap(p2, p3);
    }

    if (p1.y == p2.y) {
        DrawTriangleTop(buffer, color, p1, p2, p3);
    } else {
        if (p2.y == p3.y) {
            DrawTriangleBottom(buffer, color, p1, p2, p3);
        } else {
            int new_x = p1.x + (int)(0.5f + (float)(p2.y - p1.y) * (float)(p3.x - p1.x) / (float)(p3.y - p1.y));

            //Draw_Bottom_Tri16(p1.x,p1.y,new_x,y2,p2.x,y2,color, dest_buffer, mempitch);
            //Draw_Top_Tri16(p2.x,y2,new_x,y2,p3.x,p3.y,color, dest_buffer, mempitch);

            DrawTriangleBottom(buffer, color, p1, {new_x, p2.y}, p2);
            DrawTriangleTop(buffer, color, p2, {new_x, p2.y}, p3);
        }
    }
}

void RaceScene::DrawTriangleTop(Framebuffer& buffer, const Color& color, Point p1, Point p2, Point p3) {
    // if (p1.y == p3.y || p2.y == p3.y) {
    //     return;
    // }
    //
    // if (p2.x < p1.x) {
    //     std::swap(p1, p2);
    // }
    //
    // int height = p3.y - p1.y;
    //
    // int dx_left  = ((p3.x - p1.x) << FIXP16_SHIFT) / height;
    // int dx_right = ((p3.x - p2.x) << FIXP16_SHIFT) / height;

    int min_clip_x = 0;
    int max_clip_x = 639;
    int min_clip_y = 0;
    int max_clip_y = 479;

    uint8_t* dest_buffer = nullptr;

    int mempitch = 3;

    float dx_right,    // the dx/dy ratio of the right edge of line
        dx_left,     // the dx/dy ratio of the left edge of line
        xs,xe,       // the starting and ending points of the edges
        height;      // the height of the triangle

    int temp_y,
        right,         // used by clipping
        left;

    uint8_t* dest_addr = NULL;

    if (p2.x < p1.x) {
        std::swap(p1, p2);
    }

    height = p3.y - p1.y;

    dx_left  = (p3.x - p1.x) / height;
    dx_right = (p3.x - p2.x) / height;

    xs = (float)p1.x;
    xe = (float)p2.x + 0.5f;

    if (p1.y < 0) {
        xs = xs + dx_left * (float)(-p1.y + min_clip_y);
        xe = xe + dx_right * (float)(-p1.y + min_clip_y);

        p1.y = 0;

    }

    if (p3.y > max_clip_y) {
        p3.y = max_clip_y;
    }

    dest_addr = dest_buffer + p1.y * mempitch;

    if (p1.x >= min_clip_x && p1.x <= max_clip_x &&
        p2.x >= min_clip_x && p2.x <= max_clip_x &&
        p3.x >= min_clip_x && p3.x <= max_clip_x) {

        for (temp_y = p1.y; temp_y <= p3.y; temp_y++, dest_addr += mempitch) {

            // memset((UCHAR*)dest_addr + (unsigned int)xs, color, (unsigned int)((int)xe - (int)xs + 1));

            // __asm__(
            //     "mov edi, dest"
            //     "mov ecx, count"
            //     "mov ax,  data"
            //     "rep stosw"
            // );

            draw_line(buffer, xs, temp_y, xe, temp_y, color);

            xs += dx_left;
            xe += dx_right;

        }
    } else {
        for (temp_y = p1.y; temp_y <= p3.y; temp_y++, dest_addr += mempitch) {
            left  = (int)xs;
            right = (int)xe;

            xs += dx_left;
            xe += dx_right;

            if (left < min_clip_x) {
                left = min_clip_x;

                if (right < min_clip_x) {
                    continue;
                }
            }

            if (right > max_clip_x) {
                right = max_clip_x;

                if (left > max_clip_x) {
                    continue;
                }
            }

            // memset((UCHAR*)dest_addr + (unsigned int)left, color, (unsigned int)(right - left + 1));

            draw_line(buffer, left, temp_y, right - left + 1, temp_y, color);
        }
    }
}

void RaceScene::DrawTriangleBottom(Framebuffer& buffer, const Color& color, Point p1, Point p2, Point p3) {
    float dx_right,    // the dx/dy ratio of the right edge of line
        dx_left,     // the dx/dy ratio of the left edge of line
        xs,xe,       // the starting and ending points of the edges
        height;      // the height of the triangle

    int temp_y,
        right,         // used by clipping
        left;

    int min_clip_x = 0;
    int max_clip_x = 639;
    int min_clip_y = 0;
    int max_clip_y = 479;

    if (p3.x < p2.x) {
        std::swap(p2, p3);
    }

    height = p3.y - p1.y;

    dx_left  = (p2.x - p1.x) / height;
    dx_right = (p3.x - p1.x) / height;

    xs = (float)p1.x;
    xe = (float)p1.x; // +(float)0.5;

    if (p1.y < min_clip_y) {
        xs = xs + dx_left * (float)(-p1.y + min_clip_y);
        xe = xe + dx_right * (float)(-p1.y + min_clip_y);

        p1.y = min_clip_y;
    }

    if (p3.y > max_clip_y) {
        p3.y = max_clip_y;
    }

    if (p1.x >= min_clip_x && p1.x <= max_clip_x &&
        p2.x >= min_clip_x && p2.x <= max_clip_x &&
        p3.x >= min_clip_x && p3.x <= max_clip_x) {

        for (temp_y = p1.y; temp_y <= p3.y; temp_y++/*, dest_addr += mempitch*/) {
            // memset((UCHAR  *)dest_addr+(unsigned int)xs, color,(unsigned int)((int)xe-(int)xs+1));

            // std::cout << xs << ", " << xe << std::endl;

            draw_line(buffer, xs, temp_y, xe, temp_y, color);

        // std::cout << temp_y << ", " << xs << ", " << (int)xe - (int)xs + 1 << std::endl;

            xs += dx_left;
            xe += dx_right;
        }
    } else {
        for (temp_y = p1.y; temp_y <= p3.y; temp_y++/*, dest_addr += mempitch*/) {
            left  = (int)xs;
            right = (int)xe;

            xs += dx_left;
            xe += dx_right;

            if (left < min_clip_x) {
                left = min_clip_x;

                if (right < min_clip_x) {
                    continue;
                }
            }

            if (right > max_clip_x) {
                right = max_clip_x;

                if (left > max_clip_x) {
                    continue;
                }
            }

            // memset((UCHAR  *)dest_addr+(unsigned int)left, color,(unsigned int)(right-left+1));

            draw_line(buffer, left, temp_y, right - left + 1, temp_y, color);

        }
    }
}

/*
 * Createize  edge buckets from the given edges
 * @param n    Number of vertices
 * @param x[]  array of x points
 * @param y[]  array of y points
 * @return     List of edge buckets
 */
// void create_edges(n, x[], y[]) {
//     instantiate a new edge table
//     loop through x[] & y[] pairs {
//         if the edge's slope is NOT undefined (verticle) {
//             create bucket with edge
//             add bucket to edge table
//         }
//     }
// }


/*
 * Given the edge table of the polygon, fill the polygons
 * @param edgeTable The polygon's edge table representation
 */
// processEdgeTable (edgeTable) {
//     while (edge table is NOT empty) {
//     // Remove edges from the active list if y == ymax
//         if (active list is NOT empty) {
//             for (iterate through all buckets in the active list) {
//                 if (current bucket's ymax == current scanline) {
//                     remove bucket from active list
//                     remove bucket from edge table
//                 }
//             }
//         }
// // Add edge from edge table to active list if y == ymin
//         for (iterate through the bucket in the edge table) {
//             if (bucket's ymin == scanline) {
//                 add bucket to active list
//             }
//         }
// // Sort active list by x position and slope
//         sortTheActiveList();
// // Fill the polygon pixel
//         for (iterate through the active list) {
//             for (from vertep1.x.x to vertep2.x.x of the bucket) {
//                 setPixelColor()
//             }
//         }
// // Increment X variables of buckets based on the slope
//         for (all buckets in the active list) {
//             if (bucketsdX != 0) {
//                 bucket's sum += bucket's dX
//        while (bucket's sum >= bucket's dY) {
//             increment or decrement bucket's X depending on sign of   bucket's slope
//             edge's sum -= dY
//                 }
//             }
//         }
//     }
// }
//
/*
 * Draw a filled polygon in the Canvas C.
 * The polygon has n distinct vertices.  The coordinates of the vertices
 * making up the polygon are stored in the x and y arrays.  The ith
 * vertex will have coordinate (x[i],y[i]).
 * @param n - number of vertices
 * @param x - x coordinates
 * @param y - y coordinates
 */
// void drawPolygon(n, x[], y[]) {
//     // Create edge table
//     finalEdgeTable = createEdges()
//     // Sort edges by minY
//     sort(finalEdgeTable)
//     processEdgeTable(finalEdgeTable)
// }
