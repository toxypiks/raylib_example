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

  SetTargetFPS(SCREEN_FPS);

  Vector2 dvd_position = {0};
  Vector2 dvd_velocity = {DVD_VELOCITY * DELTA_TIME,
                          DVD_VELOCITY * DELTA_TIME
  };

  while (!WindowShouldClose()) {
	if (dvd_position.y + dvd.height * DVD_SCALING > SCREEN_HEIGHT || dvd_position.y < 0) {
	  dvd_velocity.y = -dvd_velocity.y;
	}
	if (dvd_position.x + dvd.width * DVD_SCALING > SCREEN_WIDTH || dvd_position.x < 0) {
	  dvd_velocity.x = -dvd_velocity.x;
	}

	dvd_position = Vector2Add(dvd_position, dvd_velocity);

	BeginDrawing();
	    ClearBackground(RAYWHITE);
		DrawTextureEx(dvd, dvd_position, 0.0f, DVD_SCALING, WHITE);
	EndDrawing();
  }

  CloseWindow();

  return 0;
}
