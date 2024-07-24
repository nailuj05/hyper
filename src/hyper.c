#include "hyper.h"
#include "math4d.h"
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stdlib.h>

#define SW 800
#define SH 600

int main(int argc, char *argv[]) {
  InitWindow(SW, SH, "hyper");

  Shader pixel = LoadShader(0, "resources/shaders/pixel.glsl");

  RenderTexture2D target = LoadRenderTexture(SW, SH);

  Camera camera = {0};
  camera.position = (Vector3){3.0f, 3.0f, 2.0f};
  camera.target = (Vector3){0.0f, 0.0f, 0.0f};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 55.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  Vector3 position = {0.f, 0.f, 0.f};
  Color background = {0x0F, 0x23, 0x28};

  SetTargetFPS(60);

  // Tesseract
  Vertex4D vertices4D[16] = {
      {-1, -1, -1, -1}, {-1, -1, -1, 1}, {-1, -1, 1, -1}, {-1, -1, 1, 1},
      {-1, 1, -1, -1},  {-1, 1, -1, 1},  {-1, 1, 1, -1},  {-1, 1, 1, 1},
      {1, -1, -1, -1},  {1, -1, -1, 1},  {1, -1, 1, -1},  {1, -1, 1, 1},
      {1, 1, -1, -1},   {1, 1, -1, 1},   {1, 1, 1, -1},   {1, 1, 1, 1}};

  Vector3 vertices3D[16];

  // clang-format off
  int edgeList[] = {
    0,1, 0,2, 0,4, 0,8,
    1,3, 1,5, 1,9, 
    2,3, 2,6, 2,10,
    3,7, 3,11,
    4,5, 4,6, 4,12,
    5,7, 5,13, 
    6,7, 6,14, 
    7,15,
    8,9, 8,10, 8,12,
    9,11, 9,13,
    10,11, 10,14,
    11,15,
    12,13, 12,14,
    13,15,
    14,15};
  // clang-format on

  char *plane = "yw";
  double rotationMatrix[4][4];

  while (!WindowShouldClose()) {
    UpdateCamera(&camera, CAMERA_ORBITAL);

    BeginTextureMode(target);
    ClearBackground(background);

    BeginMode3D(camera);

    rlSetLineWidth(5.0f);

    // Rotate Tesseract
    double angle = PI * sin(GetTime()) * 0.01f;
    GetRotationMatrix(angle, plane, rotationMatrix);
    for (int i = 0; i < 16; i++) {
      MulMatrixVector4D(rotationMatrix, &vertices4D[i]);
      vertices3D[i] = ProjectTo3D(vertices4D[i]);
    }

    for (int i = 0; i < 64; i += 2) {
      Vector3 edgeStart = vertices3D[edgeList[i]];
      Vector3 edgeEnd = vertices3D[edgeList[i + 1]];
      DrawLine3D(edgeStart, edgeEnd, ORANGE);
    };

    EndMode3D();

    EndTextureMode();

    BeginDrawing();

    // Post Processing
    BeginShaderMode(pixel);
    DrawTextureRec(target.texture,
                   (Rectangle){0, 0, (float)target.texture.width,
                               (float)-target.texture.height},
                   (Vector2){0, 0}, WHITE);
    EndShaderMode();

    EndDrawing();
  }

  UnloadShader(pixel);
  UnloadRenderTexture(target); // Unload render texture
  CloseWindow();

  return EXIT_SUCCESS;
}
