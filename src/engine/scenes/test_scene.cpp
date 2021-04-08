#include "test_scene.h"
#include "../renderer.h"
#include "../object.h"
#include "../camera.h"

const Color PINK = {255,   0, 127, 255};
const Color GREY = { 32,  32,  32, 255};

TestScene::TestScene(Renderer& renderer) : renderer_(renderer) {
    camera_ = new Camera();

    object_ = new Object("../assets/teapot.obj");
    object_->SetPosition({0.0f, 0.0f, -5.0f});
    object_->SetVertexColor(PINK);

    renderer_.FillScreen(GREY);
    renderer_.Draw(*camera_, *object_);
}

TestScene::~TestScene() {
    delete camera_;
    delete object_;
}

void TestScene::update(double dt) {
    (void)dt;
    return;
//         // vec3f line1 = v1World - v0World;
//         // vec3f line2 = v2World - v0World;
//         // vec3f Cross = cross(line1, line2).normalize();
//         // if (Cross.z < 0) {
//         //     continue;
//         // }
// 
//         vec2i v0Raster, v1Raster, v2Raster;
// //         computePixelCoordinates(v0World, v0Raster, [>worldToCamera,<] kCanvasWidth, kCanvasHeight, kImageWidth, kImageHeight);
//         // computePixelCoordinates(v1World, v1Raster, [>worldToCamera,<] kCanvasWidth, kCanvasHeight, kImageWidth, kImageHeight);
//         // computePixelCoordinates(v2World, v2Raster, [>worldToCamera,<] kCanvasWidth, kCanvasHeight, kImageWidth, kImageHeight);
//         
//         computePixelCoordinates(v0World, v0Raster, [>worldToCamera,<] kCanvasWidth, kCanvasHeight, kImageWidth, kImageHeight);
//         
//         renderer_.DrawPixel(WHITE, v0Raster.x, v0Raster.y);
// 
// //        renderer_.DrawLine(WHITE, v0Raster.x, v0Raster.y, v1Raster.x, v1Raster.y);
// //        renderer_.DrawLine(WHITE, v1Raster.x, v1Raster.y, v2Raster.x, v2Raster.y);
// //        renderer_.DrawLine(WHITE, v2Raster.x, v2Raster.y, v0Raster.x, v0Raster.y);
// 
    // }
}

