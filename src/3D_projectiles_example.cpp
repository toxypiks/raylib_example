#include <raylib.h>
#include <raymath.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_FPS 60

#define PROJS_CAP 1000
#define PROJ_WIDTH 1
#define PROJ_HEIGHT 1
#define PROJ_LEN 1
#define PROJ_COLOR BLACK
#define PROJ_VEL 1000.0
#define PROJ_LIFETIME 5.0

#define GUN_LEN 0.001

typedef float Seconds;

typedef struct {
  Seconds lifetime;
  Vector3 pos;
  Vector3 dir;
} Proj;

Proj projs[PROJS_CAP] = {0};
size_t projs_size = 0;

void draw_projs(void)
{
  for (size_t i = 0; i < PROJS_CAP; i++) {
	if (projs[i].lifetime > 0.0f) {
	  DrawCube(projs[i].pos,
			   PROJ_WIDTH,
			   PROJ_HEIGHT,
			   PROJ_LEN,
			   PROJ_COLOR);
	}
  }
}

void update_projs(void) {
  const Seconds dt = GetFrameTime();
  for (size_t i = 0; i < PROJS_CAP; ++i) {
	if (projs[i].lifetime > 0.0f) {
	  projs[i].lifetime -= dt;
	  projs[i].pos = Vector3Add(
		projs[i].pos,
		Vector3Scale(projs[i].dir, dt)); //What does Vector3Scale do?
	}
  }
}

void spawn_proj(Vector3 pos, Vector3 dir)
{
  for (size_t i = 0; i < PROJS_CAP; ++i) {
	if (projs[i].lifetime <= 0.0f) {
	  projs[i].pos = pos;
	  projs[i].dir = dir;
	  projs[i].lifetime = PROJ_LIFETIME;
	  break; //Why break here?
	}
  }
}

Vector3 camera_direction(Camera *camera)
{
  return Vector3Normalize(Vector3Subtract(camera->target, camera->position)); //What does that do exactly?
}

int main(void)
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3D_projectiles_example");

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
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
	  Vector3 dir = camera_direction(&camera);
	  spawn_proj(Vector3Add(camera.position, Vector3Scale(dir, GUN_LEN)),
				 Vector3Scale(dir, PROJ_VEL));
	}
	update_projs();
	UpdateCamera(&camera, cameraMode);

	BeginDrawing();
	{
	  ClearBackground(RAYWHITE);
	  BeginMode3D(camera);
	  {
		DrawModelEx(model, position, (Vector3){ 1.0f, 0.0f, 0.0f }, -90.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);
		draw_projs();
		DrawGrid(10, 1.0f);
	  }
	  EndMode3D();
	}
	EndDrawing();
  }
  return 0;
}
