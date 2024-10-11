#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(void)
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
			 "raylib_example");

  Camera2D camera = {0};
  camera.target = (Vector2){10.0f, 20.0f};
  camera.offset = (Vector2){SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f};
  camera.zoom = 1.0f;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

	if (IsKeyDown(KEY_RIGHT)) camera.target.x += 2;
	else if (IsKeyDown(KEY_LEFT)) camera.target.x -= 2;
	BeginDrawing();
	    ClearBackground(BLACK);
	    BeginMode2D(camera);
		DrawRectangle(0, 0, 100, 100, RED);
	    EndMode2D();
	EndDrawing();
  }

  CloseWindow();

  return 0;
}
