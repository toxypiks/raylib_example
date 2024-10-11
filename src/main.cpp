#include "raylib.h"
#include "raymath.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_FPS 60

#define DELTA_TIME (1.0f / SCREEN_FPS)
#define DVD_SCALING 0.125f
#define DVD_VELOCITY 100.0f

int main(void)
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
			 "raylib_example");

  Texture2D dvd = LoadTexture("../textures/DVD_logo.png");

  Camera2D camera = {0};
  camera.target = (Vector2){10.0f, 20.0f};
  camera.offset = (Vector2){SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f};
  camera.zoom = 1.0f;

  SetTargetFPS(SCREEN_FPS);

  Vector2 dvd_position = {0};
  Vector2 dvd_velocity = {DVD_VELOCITY * DELTA_TIME,
                          DVD_VELOCITY * DELTA_TIME
  };

  while (!WindowShouldClose()) {
	dvd_position = Vector2Add(dvd_position, dvd_velocity);

	BeginDrawing();
	    ClearBackground(RAYWHITE);
	    BeginMode2D(camera);
		DrawTextureEx(dvd, dvd_position, 0.0f, DVD_SCALING, WHITE);
	    EndMode2D();
	EndDrawing();
  }

  CloseWindow();

  return 0;
}
