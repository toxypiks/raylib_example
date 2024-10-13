#include <raylib.h>
#include <raymath.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_FPS 60

#define PROJS_CAP 1000
#define PROJ_WIDTH 0.1f
#define PROJ_HEIGHT 0.1f
#define PROJ_LEN 0.1f
#define PROJ_COLOR WHITE
#define PROJ_VEL 5.0f
#define PROJ_LIFETIME 5.0f

#define BACKGROUND_COLOR BLACK

#define PLAYER_GUN_LEN 0.5f
#define PLAYER_HEIGHT 1.0f

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

typedef struct {
  Vector3 position;
  float heigth;
} Pillar;

#define PILLARS_CAP 1
#define PILLAR_COLOR LIME

Pillar pillars[PILLARS_CAP] = {0};

void draw_pillars(void)
{
  for(size_t i = 0; i < PILLARS_CAP; ++i) {
	DrawCubeV(pillars[i].position, (Vector3) {1.0f, 2.0f, 1.0f}, PILLAR_COLOR);
  }
}

Vector3 camera_direction(Camera *camera)
{
  return Vector3Normalize(Vector3Subtract(camera->target, camera->position)); //What does that do exactly?
}

#define V3_Fmt "{%f, %f, %f}"
#define V3_Arg(v3) v3.x, v3.y, v3.z

char hud_buffer[1024];

int main(void)
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3D_projectiles_example");

  Camera camera = {0};
  camera.position = (Vector3){1.0f, PLAYER_HEIGHT, 1.0f};
  camera.target = (Vector3){0.0f, 0.0f, 0.0f};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  int cameraMode = CAMERA_FIRST_PERSON;

  Model model = LoadModel("../models/guy.iqm");
  Texture2D texture = LoadTexture("../textures/guytex.png");
  SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);

  Vector3 position = (Vector3){0.0f, 0.0f, 0.0f};

  DisableCursor();
  SetTargetFPS(SCREEN_FPS);

  while (!WindowShouldClose())
  {
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
	  Vector3 dir = camera_direction(&camera);
	  spawn_proj(Vector3Add(camera.position, Vector3Scale(dir, PLAYER_GUN_LEN)),
				 Vector3Scale(dir, PROJ_VEL));
	}
	update_projs();
	UpdateCamera(&camera, cameraMode);

	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
	  camera.target = (Vector3) {0.0f, 0.0f , 0.0f};
	}

	BeginDrawing();
	{
	  ClearBackground(BACKGROUND_COLOR);
	  BeginMode3D(camera);
	  {
		// DrawModelEx(model, position, (Vector3){ 1.0f, 0.0f, 0.0f }, -90.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);
		draw_projs();
		draw_pillars();
		DrawGrid(10, 1.0f);
	  }
	  EndMode3D();
	  snprintf(hud_buffer, sizeof(hud_buffer),
			   "Target: " V3_Fmt, V3_Arg(camera.target));
		DrawText(hud_buffer, 10, 10, 20, MAROON);
	}
	EndDrawing();
  }
  return 0;
}
