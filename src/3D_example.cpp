#include <raylib.h>

#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_FPS 60

int main(void)
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib_3D_example");

  Camera camera = {0};
  camera.position = (Vector3){10.0f, 10.0f, 10.0f};
  camera.target = (Vector3){0.0f, 0.0f, 0.0f};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  int cameraMode = CAMERA_FIRST_PERSON;

  Model model = LoadModel("../models/guy.iqm");
  Texture2D texture = LoadTexture("../textures/guytex.png");
  SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);

  Vector3 position = {0};

  DisableCursor();
  SetTargetFPS(SCREEN_FPS);

  while (!WindowShouldClose())
  {
	if (IsKeyPressed(KEY_ONE))
        {
            cameraMode = CAMERA_FREE;
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
        }

	if (IsKeyPressed(KEY_TWO))
        {
            cameraMode = CAMERA_FIRST_PERSON;
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
        }

	if (IsKeyPressed(KEY_THREE))
        {
            cameraMode = CAMERA_THIRD_PERSON;
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
        }

	if (IsKeyPressed(KEY_FOUR))
        {
            cameraMode = CAMERA_ORBITAL;
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
        }
	UpdateCamera(&camera, cameraMode);

	BeginDrawing();
	{
	  ClearBackground(RAYWHITE);
	  BeginMode3D(camera);
	  {
		DrawModelEx(model, position, (Vector3){ 1.0f, 0.0f, 0.0f }, -90.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);
	  }
	  EndMode3D();
	}
	EndDrawing();
  }
  return 0;
}
