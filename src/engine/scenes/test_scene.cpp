#include "test_scene.h"
#include "../renderer.h"

#include <vector>

#include <iostream>
#include "../loader.h"

#include "../object.h"
#include "../camera.h"

// FIXME: replase with proper projection matrix
mat4 cameraToWorld = {
    0.871214,   0,          -0.490904,  0,
    -0.192902,  0.919559,   -0.342346,  0,
    0.451415,   0.392953,   0.801132,   0,
    14.777467,  29.361945,  27.993464,  1};

const float kCanvasWidth = 2, kCanvasHeight = 2;
const uint32_t kImageWidth = 800, kImageHeight = 600;

mat4 orthographic;
mat4 perspective;

// http://www.songho.ca/opengl/gl_camera.html

// TODO: move all constans from here later
const Color WHITE        = {255, 255, 255, 255};
const Color GREEN        = {  0, 255,   0, 255};
const Color DARK_GREEN   = { 48, 143,  56, 255};
const Color RED          = {255,   0,   0, 255};
const Color BLUE         = {  37,101, 121, 255};
const Color GREY         = {128, 128, 128, 255};

mat4 worldToCamera;

TestScene::TestScene(Renderer& renderer) : renderer_(renderer) {
    renderer_.FillScreen(BLUE);

    object_ = new Object("../assets/tree.obj");

    // std::ofstream ofs;
    // ofs.open("./proj.svg");
    // ofs << "<svg version=\"1.1\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns=\"http://www.w3.org/2000/svg\" height=\"512\" width=\"512\">" << std::endl;


    cameraToWorld = cameraToWorld.transpose();
    worldToCamera = cameraToWorld.inverse();

    // mat4 rotation = mat4_rotate_z(45);
    // 
    // // std::cout << rotation << std::endl;
    // 
    // for (uint32_t i = 0; i < numTrisUsed; ++i) {
    //     // const vec3f &v0World = verts[tris[i * 3]];
    //     // const vec3f &v1World = verts[tris[i * 3 + 1]];
    //     // const vec3f &v2World = verts[tris[i * 3 + 2]];
    // 
    //     vec3f v0World = verts[tris[i * 3]];
    //     vec3f v1World = verts[tris[i * 3 + 1]];
    //     vec3f v2World = verts[tris[i * 3 + 2]];
    // 
    //     // std::cout << "original points:" << "\n";
    //     // std::cout << v0World << "\n";
    //     // std::cout << v1World << "\n";
    //     // std::cout << v2World << "\n";
    // 
    //     v0World = rotation * v0World;
    //     v1World = rotation * v1World;
    //     v2World = rotation * v2World;
    // 
    //     // std::cout << "translated points:" << "\n";
    //     // std::cout << v0World << "\n";
    //     // std::cout << v1World << "\n";
    //     // std::cout << v2World << "\n";
    // 
    //     vec2i v0Raster, v1Raster, v2Raster;
    //     computePixelCoordinates(v0World, v0Raster, worldToCamera, kCanvasWidth, kCanvasHeight, kImageWidth, kImageHeight);
    //     computePixelCoordinates(v1World, v1Raster, worldToCamera, kCanvasWidth, kCanvasHeight, kImageWidth, kImageHeight);
    //     computePixelCoordinates(v2World, v2Raster, worldToCamera, kCanvasWidth, kCanvasHeight, kImageWidth, kImageHeight);
    // 
    //     // ofs << "<line x1=\"" << v0Raster.x << "\" y1=\"" << v0Raster.y << "\" x2=\"" << v1Raster.x << "\" y2=\"" << v1Raster.y << "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />\n";
    //     // ofs << "<line x1=\"" << v1Raster.x << "\" y1=\"" << v1Raster.y << "\" x2=\"" << v2Raster.x << "\" y2=\"" << v2Raster.y << "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />\n";
    //     // ofs << "<line x1=\"" << v2Raster.x << "\" y1=\"" << v2Raster.y << "\" x2=\"" << v0Raster.x << "\" y2=\"" << v0Raster.y << "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />\n";
    // 
    //     renderer_.DrawLine(WHITE, v0Raster.x, v0Raster.y, v1Raster.x, v1Raster.y);
    //     renderer_.DrawLine(WHITE, v1Raster.x, v1Raster.y, v2Raster.x, v2Raster.y);
    //     renderer_.DrawLine(WHITE, v2Raster.x, v2Raster.y, v0Raster.x, v0Raster.y);
    // 
    // }
    // 
    // ofs << "</svg>\n";
    // ofs.close();

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
}

TestScene::~TestScene() {
    delete object_;
}

float da = 30.0f;
static float angle = 0.0f;
void TestScene::update(double dt) {
    renderer_.FillScreen(BLUE);

    const std::vector<vec3f>& verts = object_->GetVertices();
    const std::vector<uint16_t> tris = object_->GetTriangles();

    const uint16_t numTrisUsed = verts.size();

    angle = angle + da * dt;
    mat4 rotation = mat4_rotate_x(angle);

    for (uint32_t i = 0; i < numTrisUsed; ++i) {
        vec3f v0World = verts[tris[i * 3]];
        vec3f v1World = verts[tris[i * 3 + 1]];
        vec3f v2World = verts[tris[i * 3 + 2]];

        // std::cout << "original points:" << "\n";
        // std::cout << v0World << "\n";
        // std::cout << v1World << "\n";
        // std::cout << v2World << "\n";

        v0World = rotation * v0World;
        v1World = rotation * v1World;
        v2World = rotation * v2World;

        // std::cout << "translated points:" << "\n";
        // std::cout << v0World << "\n";
        // std::cout << v1World << "\n";
        // std::cout << v2World << "\n";

        vec2i v0Raster, v1Raster, v2Raster;
        computePixelCoordinates(v0World, v0Raster, worldToCamera, kCanvasWidth, kCanvasHeight, kImageWidth, kImageHeight);
        computePixelCoordinates(v1World, v1Raster, worldToCamera, kCanvasWidth, kCanvasHeight, kImageWidth, kImageHeight);
        computePixelCoordinates(v2World, v2Raster, worldToCamera, kCanvasWidth, kCanvasHeight, kImageWidth, kImageHeight);

        renderer_.DrawLine(WHITE, v0Raster.x, v0Raster.y, v1Raster.x, v1Raster.y);
        renderer_.DrawLine(WHITE, v1Raster.x, v1Raster.y, v2Raster.x, v2Raster.y);
        renderer_.DrawLine(WHITE, v2Raster.x, v2Raster.y, v0Raster.x, v0Raster.y);

    }
}

void TestScene::computePixelCoordinates(const vec3f pWorld,
                                        vec2i &pRaster,
                                        const mat4 &worldToCamera,
                                        const float &canvasWidth,
                                        const float &canvasHeight,
                                        const uint32_t &imageWidth,
                                        const uint32_t &imageHeight) {
    vec4f pCamera = worldToCamera * vec4f(pWorld, 1.0f);
    vec2f pScreen;
    pScreen.x = pCamera.x / -pCamera.z;
    pScreen.y = pCamera.y / -pCamera.z;
    vec2f pNDC;
    pNDC.x = (pScreen.x + canvasWidth * 0.5f) / canvasWidth;
    pNDC.y = (pScreen.y + canvasHeight * 0.5f) / canvasHeight;
    pRaster.x = (int)(pNDC.x * imageWidth);
    pRaster.y = (int)((1 - pNDC.y) * imageHeight);
}
