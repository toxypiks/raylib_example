#include <raylib.h>
#include <raymath.h>

#include <stdlib.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_FPS 60

#define PROJS_CAP 69
#define PROJ_WIDTH 100
#define PROJ_HEIGHT 100
#define PROJ_LEN 100
#define PROJ_COLOR BLACK

typedef struct {
  bool alive;
  Vector3 pos;
  Vector3 dir;
} Proj;

Proj projs[PROJS_CAP] = {0};
size_t projs_size = 0;

void draw_projs(void)
{
  for (size_t i = 0; i < PROJS_CAP; i++) {
	if (projs[i].alive) {
	  DrawCube(projs[i].pos, PROJ_WIDTH, PROJ_HEIGHT, PROJ_LEN, PROJ_COLOR);
	}
  }
}

void update_projs(void) {
  for (size_t i = 0; i < PROJS_CAP; ++i) {
	if (projs[i].alive) {
	  projs[i].pos = Vector3Add(
		projs[i].pos,
		Vector3Scale(projs[i].dir, GetFrameTime())); //What does Vector3Scale do?
	}
  }
}

void spawn_proj(Vector3 pos, Vector3 dir)
{
  for (size_t i = 0; i < PROJS_CAP; ++i) {
	if (!projs[i].alive) {
	  projs[i].pos = pos;
	  projs[i].dir = dir;
	  projs[i].alive = true;
	  break; //Why break here?
	}
  }
}

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
		for (size_t i = 0; i < projs_size; i++) {
		  draw_projs();
		}
		DrawModelEx(model, position, (Vector3){ 1.0f, 0.0f, 0.0f }, -90.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);
		DrawGrid(10, 1.0f);
	  }
	  EndMode3D();
	}
	EndDrawing();
  }
  return 0;
}
