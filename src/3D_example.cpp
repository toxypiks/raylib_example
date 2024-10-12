#include <raylib.h>

#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_FPS 60

int main(void)
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib_3d_example");

  SetTargetFPS(SCREEN_FPS);

  while (!WindowShouldClose()) {
	BeginDrawing();
	{
	  ClearBackground(RAYWHITE);
	}
	EndDrawing();
  }
  return 0;
}
