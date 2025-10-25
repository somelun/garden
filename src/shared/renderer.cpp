#include "renderer.h"
#include "framebuffer.h"

#include <utility>

void Renderer::SetTarget(Framebuffer* fb) {
    target = fb;
}

// void Renderer::Draw(const Camera& camera, const std::vector<Object>& objects) {
//     for (const Object& object : objects) {
//         Draw(camera, object);
//     }
// }

// void Renderer::Draw(const Camera& camera, const Object& object) {
//         const std::vector<vec3f>& vertices = object.GetVertices();
// 
//         // TODO: add back triagnles, not only vertices
//         // const std::vector<uint16_t> triangles = object.GetTriangles();
//         // const uint16_t numTriangles = triangles.size();
// 
//         mat4 translation = mat4_translate(object.GetPosition());
// 
//         const uint16_t numVertices = vertices.size();
//         for (uint32_t i = 0; i < numVertices; ++i) {
// 
//             vec3f translated = translation * vertices[i];
// 
//             vec2i rastered = ComputePixelCoordinates(camera.projection, translated);
// 
//             DrawPixel(object.GetVertexColor(), rastered.x, rastered.y);
//         }
// }

// void Renderer::DrawTriangle2D(const Color& color, Point p1, Point p2, Point p3) {
//     // check for horizontal or vertical
//     if ((p1.x == p2.x && p2.x == p3.x) || (p1.y == p2.y && p2.y == p3.y)) {
//         return;
//     }
// 
//     if (p2.y < p1.y) {
//         std::swap(p1, p2);
//     }
// 
//     if (p3.y < p1.y) {
//         std::swap(p1, p3);
//     }
// 
//     if (p3.y < p2.y) {
//         std::swap(p2, p3);
//     }
// 
//     if (p1.y == p2.y) {
//         DrawTriangleTop(color, p1, p2, p3);
//     } else {
//         if (p2.y == p3.y) {
//             DrawTriangleBottom(color, p1, p2, p3);
//         } else {
//             int new_x = p1.x + (int)(0.5f + (float)(p2.y - p1.y) * (float)(p3.x - p1.x) / (float)(p3.y - p1.y));
// 
//             DrawTriangleBottom(color, p1, {new_x, p2.y}, p2);
//             DrawTriangleTop(color, p2, {new_x, p2.y}, p3);
//         }
//     }
// }

// void Renderer::DrawTriangleTop(const Color& color, Point p1, Point p2, Point p3) {
//     // if (p1.y == p3.y || p2.y == p3.y) {
//     //     return;
//     // }
//     //
//     // if (p2.x < p1.x) {
//     //     std::swap(p1, p2);
//     // }
//     //
//     // int height = p3.y - p1.y;
//     //
//     // int dx_left  = ((p3.x - p1.x) << FIXP16_SHIFT) / height;
//     // int dx_right = ((p3.x - p2.x) << FIXP16_SHIFT) / height;
// 
//     int min_clip_x = 0;
//     int max_clip_x = 639;
//     int min_clip_y = 0;
//     int max_clip_y = 479;
// 
//     uint8_t* dest_framebuffer_ = nullptr;
// 
//     int mempitch = 3;
// 
//     float dx_right,    // the dx/dy ratio of the right edge of line
//         dx_left,     // the dx/dy ratio of the left edge of line
//         xs,xe,       // the starting and ending points of the edges
//         height;      // the height of the triangle
// 
//     int temp_y,
//         right,         // used by clipping
//         left;
// 
//     uint8_t* dest_addr = NULL;
// 
//     if (p2.x < p1.x) {
//         std::swap(p1, p2);
//     }
// 
//     height = p3.y - p1.y;
// 
//     dx_left  = (p3.x - p1.x) / height;
//     dx_right = (p3.x - p2.x) / height;
// 
//     xs = (float)p1.x;
//     xe = (float)p2.x + 0.5f;
// 
//     if (p1.y < 0) {
//         xs = xs + dx_left * (float)(-p1.y + min_clip_y);
//         xe = xe + dx_right * (float)(-p1.y + min_clip_y);
// 
//         p1.y = 0;
// 
//     }
// 
//     if (p3.y > max_clip_y) {
//         p3.y = max_clip_y;
//     }
// 
//     dest_addr = dest_framebuffer_ + p1.y * mempitch;
// 
//     if (p1.x >= min_clip_x && p1.x <= max_clip_x &&
//         p2.x >= min_clip_x && p2.x <= max_clip_x &&
//         p3.x >= min_clip_x && p3.x <= max_clip_x) {
// 
//         for (temp_y = p1.y; temp_y <= p3.y; temp_y++, dest_addr += mempitch) {
// 
//             // memset((UCHAR*)dest_addr + (unsigned int)xs, color, (unsigned int)((int)xe - (int)xs + 1));
// 
//             // __asm__(
//             //     "mov edi, dest"
//             //     "mov ecx, count"
//             //     "mov ax,  data"
//             //     "rep stosw"
//             // );
// 
//             DrawLine(color, xs, temp_y, xe, temp_y);
// 
//             xs += dx_left;
//             xe += dx_right;
// 
//         }
//     } else {
//         for (temp_y = p1.y; temp_y <= p3.y; temp_y++, dest_addr += mempitch) {
//             left  = (int)xs;
//             right = (int)xe;
// 
//             xs += dx_left;
//             xe += dx_right;
// 
//             if (left < min_clip_x) {
//                 left = min_clip_x;
// 
//                 if (right < min_clip_x) {
//                     continue;
//                 }
//             }
// 
//             if (right > max_clip_x) {
//                 right = max_clip_x;
// 
//                 if (left > max_clip_x) {
//                     continue;
//                 }
//             }
// 
//             // memset((UCHAR*)dest_addr + (unsigned int)left, color, (unsigned int)(right - left + 1));
// 
//             DrawLine(color, left, temp_y, right - left + 1, temp_y);
//         }
//     }
// }

// void Renderer::DrawTriangleBottom(const Color& color, Point p1, Point p2, Point p3) {
//     float dx_right,    // the dx/dy ratio of the right edge of line
//         dx_left,     // the dx/dy ratio of the left edge of line
//         xs,xe,       // the starting and ending points of the edges
//         height;      // the height of the triangle
// 
//     int temp_y,
//         right,         // used by clipping
//         left;
// 
//     int min_clip_x = 0;
//     int max_clip_x = 639;
//     int min_clip_y = 0;
//     int max_clip_y = 479;
// 
//     if (p3.x < p2.x) {
//         std::swap(p2, p3);
//     }
// 
//     height = p3.y - p1.y;
// 
//     dx_left  = (p2.x - p1.x) / height;
//     dx_right = (p3.x - p1.x) / height;
// 
//     xs = (float)p1.x;
//     xe = (float)p1.x; // +(float)0.5;
// 
//     if (p1.y < min_clip_y) {
//         xs = xs + dx_left * (float)(-p1.y + min_clip_y);
//         xe = xe + dx_right * (float)(-p1.y + min_clip_y);
// 
//         p1.y = min_clip_y;
//     }
// 
//     if (p3.y > max_clip_y) {
//         p3.y = max_clip_y;
//     }
// 
//     if (p1.x >= min_clip_x && p1.x <= max_clip_x &&
//         p2.x >= min_clip_x && p2.x <= max_clip_x &&
//         p3.x >= min_clip_x && p3.x <= max_clip_x) {
// 
//         for (temp_y = p1.y; temp_y <= p3.y; temp_y++[>, dest_addr += mempitch<]) {
//             // memset((UCHAR  *)dest_addr+(unsigned int)xs, color,(unsigned int)((int)xe-(int)xs+1));
// 
//             // std::cout << xs << ", " << xe << std::endl;
// 
//             DrawLine(color, xs, temp_y, xe, temp_y);
// 
//         // std::cout << temp_y << ", " << xs << ", " << (int)xe - (int)xs + 1 << std::endl;
// 
//             xs += dx_left;
//             xe += dx_right;
//         }
//     } else {
//         for (temp_y = p1.y; temp_y <= p3.y; temp_y++[>, dest_addr += mempitch<]) {
//             left  = (int)xs;
//             right = (int)xe;
// 
//             xs += dx_left;
//             xe += dx_right;
// 
//             if (left < min_clip_x) {
//                 left = min_clip_x;
// 
//                 if (right < min_clip_x) {
//                     continue;
//                 }
//             }
// 
//             if (right > max_clip_x) {
//                 right = max_clip_x;
// 
//                 if (left > max_clip_x) {
//                     continue;
//                 }
//             }
// 
//             // memset((UCHAR  *)dest_addr+(unsigned int)left, color,(unsigned int)(right-left+1));
// 
//             DrawLine(color, left, temp_y, right - left + 1, temp_y);
// 
//         }
//     }
// }

// void Renderer::DrawQuad(const Color& color, Point p1, Point p2, Point p3, Point p4) {
//     DrawTriangle2D(color, p1, p2, p3);
//     DrawTriangle2D(color, p2, p3, p4);
// }
// 
void Renderer::FillScreen(const Color& color) {
    size_t size = target->width * target->height * 4;

    uint32_t c = PackedColor(color);
    target->data[0] = c;
    size_t filled = 1;

    while (filled < size) {
        size_t copy = (filled < size - filled) ? filled : (size - filled);
        memcpy(target->data + filled, target->data, copy * sizeof(uint32_t));
        filled += copy;
    }
}

// void Renderer::DrawPixel(const Color& color, uint16_t x, uint16_t y) {
//     // FIXME:
//     if (x > 799 || y > 599) {
//         return;
//     }
// 
//     uint32_t* data = target->data;
// 
//     uint32_t index = (y * target->width + x) * 4;
//     data[index]     = color.x;
//     data[index + 1] = color.y;
//     data[index + 2] = color.z;
//     data[index + 3] = color.w;
// }

// https://haqr.eu/tinyrenderer/bresenham/
void Renderer::DrawLine(Point2D p1, Point2D p2, const Color& color) {
    bool steep = std::abs(p1.x - p2.x) < std::abs(p1.y - p2.y);

    if (steep) { // if the line is steep, we transpose the image
        std::swap(p1.x, p1.y);
        std::swap(p2.x, p2.y);
    }

    if (p1.x > p2.x) { // make it left−to−right
        std::swap(p1, p2);
    }

    const uint32_t packed_color = PackedColor(color);

    int y = p1.y;
    int ierror = 0;
    for (int x = p1.x; x <= p2.x; ++x) {

        if (steep) { // if transposed, de−transpose
            const uint32_t index = x * target->width + y;
            target->data[index] = packed_color;
        } else {
            const uint32_t index = y * target->width + x;
            target->data[index] = packed_color;
        }
        ierror += 2 * std::abs(p2.y - p1.y);
        if (ierror > p2.x - p1.x) {
            y += p2.y > p1.y ? 1 : -1;
            ierror -= 2 * (p2.x - p1.x);
        }
    }
}

// const vec2i Renderer::ComputePixelCoordinates(const mat4& projection, const vec3f& pointWorld) {
//     vec4f pointProjected = projection * vec4f(pointWorld, 1.0f);
// 
//     const vec2f pointScreen = {
//         pointProjected.x / -pointProjected.z,
//         pointProjected.y / -pointProjected.z
//     };
// 
//     const vec2f pointNDC = {
//         (pointScreen.x + kCanvasWidth * 0.5f) / kCanvasWidth,
//         (pointScreen.y + kCanvasHeight * 0.5f) / kCanvasHeight
//     };
// 
//     const vec2i pointRaster = {
//         (int)((pointNDC.x) * target->width),
//         (int)((1 - pointNDC.y) * target->height)
//     };
// 
//     return pointRaster;
// }
