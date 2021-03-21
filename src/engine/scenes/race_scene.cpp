#include "race_scene.h"
#include "../renderer.h"

// #include <math.h>
#include <iostream>

#include "../object.h"
#include "../camera.h"


//#include <cstdlib>
//#include <cstdio>
#include <fstream>



const vec3f verts[146] = {
    {        0,    39.034,         0}, {  0.76212,    36.843,         0},
    {        3,    36.604,         0}, {        1,    35.604,         0},
    {   2.0162,    33.382,         0}, {        0,    34.541,         0},
    {  -2.0162,    33.382,         0}, {       -1,    35.604,         0},
    {       -3,    36.604,         0}, { -0.76212,    36.843,         0},
    {-0.040181,     34.31,         0}, {   3.2778,    30.464,         0},
    {-0.040181,    30.464,         0}, {-0.028749,    30.464,         0},
    {   3.2778,    30.464,         0}, {   1.2722,    29.197,         0},
    {   1.2722,    29.197,         0}, {-0.028703,    29.197,         0},
    {   1.2722,    29.197,         0}, {   5.2778,    25.398,         0},
    { -0.02865,    25.398,         0}, {   1.2722,    29.197,         0},
    {   5.2778,    25.398,         0}, {   3.3322,    24.099,         0},
    {-0.028683,    24.099,         0}, {   7.1957,    20.299,         0},
    { -0.02861,    20.299,         0}, {   5.2778,    19.065,         0},
    {-0.028663,    18.984,         0}, {   9.2778,    15.265,         0},
    {-0.028571,    15.185,         0}, {   9.2778,    15.265,         0},
    {   7.3772,    13.999,         0}, {-0.028625,    13.901,         0},
    {   9.2778,    15.265,         0}, {   12.278,    8.9323,         0},
    {-0.028771,    8.9742,         0}, {   12.278,    8.9323,         0},
    {   10.278,    7.6657,         0}, {-0.028592,    7.6552,         0},
    {   15.278,    2.5994,         0}, {-0.028775,    2.6077,         0},
    {   15.278,    2.5994,         0}, {   13.278,    1.3329,         0},
    {-0.028727,    1.2617,         0}, {   18.278,   -3.7334,         0},
    {   18.278,   -3.7334,         0}, {   2.2722,   -1.2003,         0},
    {-0.028727,   -1.3098,         0}, {   4.2722,        -5,         0},
    {   4.2722,        -5,         0}, {-0.028727,        -5,         0},
    {  -3.3582,    30.464,         0}, {  -3.3582,    30.464,         0},
    {  -1.3526,    29.197,         0}, {  -1.3526,    29.197,         0},
    {  -1.3526,    29.197,         0}, {  -5.3582,    25.398,         0},
    {  -1.3526,    29.197,         0}, {  -5.3582,    25.398,         0},
    {  -3.4126,    24.099,         0}, {   -7.276,    20.299,         0},
    {  -5.3582,    19.065,         0}, {  -9.3582,    15.265,         0},
    {  -9.3582,    15.265,         0}, {  -7.4575,    13.999,         0},
    {  -9.3582,    15.265,         0}, {  -12.358,    8.9323,         0},
    {  -12.358,    8.9323,         0}, {  -10.358,    7.6657,         0},
    {  -15.358,    2.5994,         0}, {  -15.358,    2.5994,         0},
    {  -13.358,    1.3329,         0}, {  -18.358,   -3.7334,         0},
    {  -18.358,   -3.7334,         0}, {  -2.3526,   -1.2003,         0},
    {  -4.3526,        -5,         0}, {  -4.3526,        -5,         0},
    {        0,     34.31,  0.040181}, {        0,    30.464,   -3.2778},
    {        0,    30.464,  0.040181}, {        0,    30.464,  0.028749},
    {        0,    30.464,   -3.2778}, {        0,    29.197,   -1.2722},
    {        0,    29.197,   -1.2722}, {        0,    29.197,  0.028703},
    {        0,    29.197,   -1.2722}, {        0,    25.398,   -5.2778},
    {        0,    25.398,   0.02865}, {        0,    29.197,   -1.2722},
    {        0,    25.398,   -5.2778}, {        0,    24.099,   -3.3322},
    {        0,    24.099,  0.028683}, {        0,    20.299,   -7.1957},
    {        0,    20.299,   0.02861}, {        0,    19.065,   -5.2778},
    {        0,    18.984,  0.028663}, {        0,    15.265,   -9.2778},
    {        0,    15.185,  0.028571}, {        0,    15.265,   -9.2778},
    {        0,    13.999,   -7.3772}, {        0,    13.901,  0.028625},
    {        0,    15.265,   -9.2778}, {        0,    8.9323,   -12.278},
    {        0,    8.9742,  0.028771}, {        0,    8.9323,   -12.278},
    {        0,    7.6657,   -10.278}, {        0,    7.6552,  0.028592},
    {        0,    2.5994,   -15.278}, {        0,    2.6077,  0.028775},
    {        0,    2.5994,   -15.278}, {        0,    1.3329,   -13.278},
    {        0,    1.2617,  0.028727}, {        0,   -3.7334,   -18.278},
    {        0,   -3.7334,   -18.278}, {        0,   -1.2003,   -2.2722},
    {        0,   -1.3098,  0.028727}, {        0,        -5,   -4.2722},
    {        0,        -5,   -4.2722}, {        0,        -5,  0.028727},
    {        0,    30.464,    3.3582}, {        0,    30.464,    3.3582},
    {        0,    29.197,    1.3526}, {        0,    29.197,    1.3526},
    {        0,    29.197,    1.3526}, {        0,    25.398,    5.3582},
    {        0,    29.197,    1.3526}, {        0,    25.398,    5.3582},
    {        0,    24.099,    3.4126}, {        0,    20.299,     7.276},
    {        0,    19.065,    5.3582}, {        0,    15.265,    9.3582},
    {        0,    15.265,    9.3582}, {        0,    13.999,    7.4575},
    {        0,    15.265,    9.3582}, {        0,    8.9323,    12.358},
    {        0,    8.9323,    12.358}, {        0,    7.6657,    10.358},
    {        0,    2.5994,    15.358}, {        0,    2.5994,    15.358},
    {        0,    1.3329,    13.358}, {        0,   -3.7334,    18.358},
    {        0,   -3.7334,    18.358}, {        0,   -1.2003,    2.3526},
    {        0,        -5,    4.3526}, {        0,        -5,    4.3526}
};

const uint32_t numTris = 128;

const uint32_t tris[numTris * 3] = {
      8,   7,   9,   6,   5,   7,   4,   3,   5,   2,   1,   3,   0,   9,   1,
      5,   3,   7,   7,   3,   9,   9,   3,   1,  10,  12,  11,  13,  15,  14,
     15,  13,  16,  13,  17,  16,  18,  20,  19,  17,  20,  21,  20,  23,  22,
     20,  24,  23,  23,  26,  25,  24,  26,  23,  26,  27,  25,  26,  28,  27,
     27,  30,  29,  28,  30,  27,  30,  32,  31,  30,  33,  32,  27,  30,  34,
     32,  36,  35,  33,  36,  32,  36,  38,  37,  36,  39,  38,  38,  41,  40,
     39,  41,  38,  41,  43,  42,  41,  44,  43,  44,  45,  43,  44,  47,  46,
     44,  48,  47,  48,  49,  47,  48,  51,  50,  10,  52,  12,  13,  53,  54,
     55,  17,  54,  13,  54,  17,  56,  57,  20,  17,  58,  20,  20,  59,  60,
     20,  60,  24,  60,  61,  26,  24,  60,  26,  26,  61,  62,  26,  62,  28,
     62,  63,  30,  28,  62,  30,  30,  64,  65,  30,  65,  33,  62,  66,  30,
     65,  67,  36,  33,  65,  36,  36,  68,  69,  36,  69,  39,  69,  70,  41,
     39,  69,  41,  41,  71,  72,  41,  72,  44,  44,  72,  73,  44,  74,  75,
     44,  75,  48,  48,  75,  76,  48,  77,  51,  78,  80,  79,  81,  83,  82,
     83,  81,  84,  81,  85,  84,  86,  88,  87,  85,  88,  89,  88,  91,  90,
     88,  92,  91,  91,  94,  93,  92,  94,  91,  94,  95,  93,  94,  96,  95,
     95,  98,  97,  96,  98,  95,  98, 100,  99,  98, 101, 100,  95,  98, 102,
    100, 104, 103, 101, 104, 100, 104, 106, 105, 104, 107, 106, 106, 109, 108,
    107, 109, 106, 109, 111, 110, 109, 112, 111, 112, 113, 111, 112, 115, 114,
    112, 116, 115, 116, 117, 115, 116, 119, 118,  78, 120,  80,  81, 121, 122,
    123,  85, 122,  81, 122,  85, 124, 125,  88,  85, 126,  88,  88, 127, 128,
     88, 128,  92, 128, 129,  94,  92, 128,  94,  94, 129, 130,  94, 130,  96,
    130, 131,  98,  96, 130,  98,  98, 132, 133,  98, 133, 101, 130, 134,  98,
    133, 135, 104, 101, 133, 104, 104, 136, 137, 104, 137, 107, 137, 138, 109,
    107, 137, 109, 109, 139, 140, 109, 140, 112, 112, 140, 141, 112, 142, 143,
    112, 143, 116, 116, 143, 144, 116, 145, 119
};


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

    
    std::ofstream ofs;
    ofs.open("./proj.svg");
    ofs << "<svg version=\"1.1\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns=\"http://www.w3.org/2000/svg\" height=\"512\" width=\"512\">" << std::endl;
    
    
    mat4 cameraToWorld = {
        0.871214,   0,          -0.490904,  0,
        -0.192902,  0.919559,   -0.342346,  0,
        0.451415,   0.392953,   0.801132,   0,
        14.777467,  29.361945,  27.993464,  1};

    cameraToWorld = cameraToWorld.transpose();
    
    mat4 worldToCamera = cameraToWorld.inverse();
    
//    std::cerr << worldToCamera << std::endl;
    float canvasWidth = 2, canvasHeight = 2;
    uint32_t imageWidth = 512, imageHeight = 512;
    
//    return 0;
    
    for (uint32_t i = 0; i < numTris; ++i) {
        const vec3f &v0World = verts[tris[i * 3]];
        const vec3f &v1World = verts[tris[i * 3 + 1]];
        const vec3f &v2World = verts[tris[i * 3 + 2]];
        vec2i v0Raster, v1Raster, v2Raster;
        computePixelCoordinates(v0World, v0Raster, worldToCamera, canvasWidth, canvasHeight, imageWidth, imageHeight);
        computePixelCoordinates(v1World, v1Raster, worldToCamera, canvasWidth, canvasHeight, imageWidth, imageHeight);
        computePixelCoordinates(v2World, v2Raster, worldToCamera, canvasWidth, canvasHeight, imageWidth, imageHeight);
//        std::cerr << v0Raster << ", " << v1Raster << ", " << v2Raster << std::endl;
        ofs << "<line x1=\"" << v0Raster.x << "\" y1=\"" << v0Raster.y << "\" x2=\"" << v1Raster.x << "\" y2=\"" << v1Raster.y << "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />\n";
        ofs << "<line x1=\"" << v1Raster.x << "\" y1=\"" << v1Raster.y << "\" x2=\"" << v2Raster.x << "\" y2=\"" << v2Raster.y << "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />\n";
        ofs << "<line x1=\"" << v2Raster.x << "\" y1=\"" << v2Raster.y << "\" x2=\"" << v0Raster.x << "\" y2=\"" << v0Raster.y << "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />\n";
    }
    
    ofs << "</svg>\n";
    ofs.close();
    
    
    
    
    
    
    
    
    
    
//    float near = 0.001f, far = 100.0f;
//    float left = 0.0f, right = 800.0f, bottom = 600.0f, top = 0.0f;
//    //
//    orthographic.at(0, 0) = 2.0f / (right - left);
//    orthographic.at(1, 1) = 2.0f / (top - bottom);
//    orthographic.at(2, 2) = -2.0f / (far - near);
//    orthographic.at(3, 3) = 1.0f;
//    orthographic.at(0, 3) = -(right + left) / (right - left);
//    orthographic.at(1, 3) = -(top + bottom) / (top - bottom);
//    orthographic.at(2, 3) = -(far + near) / (far - near);
//
//     float angleOfView = 45.0;
//     float aspectRatio = 0.75;
//
//     float size = near * tanf(degreesToRadians(angleOfView) / 2.0f);
//     left = -size, right = size, bottom = -size / aspectRatio, top = size / aspectRatio;
//
//     perspective.at(0, 0) = 2.0f * near / (right - left);
//
//     perspective.at(1, 1) = 2.0f * near / (top - bottom);
//
//     perspective.at(0, 2) = (right + left) / (right - left);
//     perspective.at(1, 2) = (top + bottom) / (top - bottom);
//     perspective.at(2, 2) = -(far + near) / (far - near);
//     perspective.at(3, 2) = -1.0f;
//
//     perspective.at(2, 3) = -(2.0f * far * near) / (far - near);
    

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
//    vec4f* verticesProjected = new vec4f[8];
    // mat4 rotationMatrix = mat4_rotate_x(angle);
    // std::cout << rotationMatrix << std::endl;
//    for (int i = 0; i < 3; ++i) {
//        vec4f vert = {object->getVertex(i), 1.0f};
//         std::cout << vert << std::endl;
        //verticesRotated[i] = rotationMatrix * vert;

        //std::cout << verticesRotated[i] << std::endl;

//        verticesProjected[i] = orthographic * vert;
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

//         std::cout << verticesProjected[i] << std::endl;
//        std::cout << "..................." << std::endl;

//        renderer_.DrawPixel(WHITE, verticesProjected[i].x, verticesProjected[i].y);
//    }
    
//    renderer_.DrawLine(WHITE, verticesProjected[0].x, verticesProjected[0].y, verticesProjected[1].x, verticesProjected[1].y);
//    renderer_.DrawLine(WHITE, verticesProjected[1].x, verticesProjected[1].y, verticesProjected[2].x, verticesProjected[2].y);
//    renderer_.DrawLine(WHITE, verticesProjected[2].x, verticesProjected[2].y, verticesProjected[0].x, verticesProjected[0].y);
    
    
//    mat4 M = {
//        0.718762f, 0.615033f, -0.324214f, 0.0f,
//        -0.393732f, 0.744416f, 0.539277f, 0.0f,
//        0.573024f, -0.259959f, 0.777216f, 0.0f,
//        0.526967f, 1.254234f, -2.532150f, 1.0f
//    };
//    M = M.transpose();
//
//    mat4 I = M.inverse();
//
//    vec4f local = {-0.5f, 0.5f, -0.5f, 1.0f};
//
//    vec4f world = M * local;
//
//    std::cout << world << std::endl;
//
//    local = I * world;
//
//    std::cout << local << std::endl;
    
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

void RaceScene::computePixelCoordinates(const vec3f pWorld,
                                        vec2i &pRaster,
                                        const mat4 &worldToCamera,
                                        const float &canvasWidth,
                                        const float &canvasHeight,
                                        const uint32_t &imageWidth,
                                        const uint32_t &imageHeight) {
    vec4f pCamera = worldToCamera * vec4f(pWorld, 1.0f);
    
    std::cout << worldToCamera << std::endl;
    
//    std::cout << pWorld.x << " " << pWorld.y << " " << pWorld.z << std::endl;
    
    vec2f pScreen;
    pScreen.x = pCamera.x / -pCamera.z;
    pScreen.y = pCamera.y / -pCamera.z;
    
//    std::cout << pScreen.x << ", " << pScreen.y << std::endl;
    
    
    vec2f pNDC;
    pNDC.x = (pScreen.x + canvasWidth * 0.5) / canvasWidth;
    pNDC.y = (pScreen.y + canvasHeight * 0.5) / canvasHeight;
    pRaster.x = (int)(pNDC.x * imageWidth);
    pRaster.y = (int)((1 - pNDC.y) * imageHeight);
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
//    for (int i = 0; i < 8; ++i) {
//        vec4f vert = {object->getVertex(i), 1.0f};
//        verticesRotated[i] = rotationMatrix * vert;
//        verticesProjected[i] = orthographic * verticesRotated[i];
//    }

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
