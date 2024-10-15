#include "raylib.h"
#include "raymath.h"
#include "stddef.h"

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


  Shader shader = LoadShader(NULL, TextFormat("../shades/wave.fs"));

  int secondsLoc = GetShaderLocation(shader, "seconds");
  int freqXLoc = GetShaderLocation(shader, "freqX");
  int freqYLoc = GetShaderLocation(shader, "freqY");
  int ampXLoc = GetShaderLocation(shader, "ampX");
  int ampYLoc = GetShaderLocation(shader, "ampY");
  int speedXLoc = GetShaderLocation(shader, "speedX");
  int speedYLoc = GetShaderLocation(shader, "speedY");

  // Shader uniform values that can be updated at any time
  float freqX = 25.0f;
  float freqY = 25.0f;
  float ampX = 10.0f;
  float ampY = 10.0f;
  float speedX = 20.0f; //8.0f
  float speedY = 20.0f;

  float screenSize[2] = { (float)GetScreenWidth(), (float)GetScreenHeight() };
  SetShaderValue(shader, GetShaderLocation(shader, "size"), &screenSize, SHADER_UNIFORM_VEC2);
  SetShaderValue(shader, freqXLoc, &freqX, SHADER_UNIFORM_FLOAT);
  SetShaderValue(shader, freqYLoc, &freqY, SHADER_UNIFORM_FLOAT);
  SetShaderValue(shader, ampXLoc, &ampX, SHADER_UNIFORM_FLOAT);
  SetShaderValue(shader, ampYLoc, &ampY, SHADER_UNIFORM_FLOAT);
  SetShaderValue(shader, speedXLoc, &speedX, SHADER_UNIFORM_FLOAT);
  SetShaderValue(shader, speedYLoc, &speedY, SHADER_UNIFORM_FLOAT);

  float seconds = 0.0f;

  SetTargetFPS(SCREEN_FPS);

  Vector2 dvd_position = {0};
  Vector2 dvd_velocity = {DVD_VELOCITY * DELTA_TIME,
                          DVD_VELOCITY * DELTA_TIME
  };

  while (!WindowShouldClose()) {

	seconds += GetFrameTime();

	SetShaderValue(shader, secondsLoc, &seconds, SHADER_UNIFORM_FLOAT);


	if (dvd_position.y + dvd.height * DVD_SCALING > SCREEN_HEIGHT || dvd_position.y < 0) {
	  dvd_velocity.y = -dvd_velocity.y;
	}
	if (dvd_position.x + dvd.width * DVD_SCALING > SCREEN_WIDTH || dvd_position.x < 0) {
	  dvd_velocity.x = -dvd_velocity.x;
	}

	dvd_position = Vector2Add(dvd_position, dvd_velocity);

	BeginDrawing();
	    ClearBackground(RAYWHITE);
		BeginShaderMode(shader);
		DrawTextureEx(dvd, dvd_position, 0.0f, DVD_SCALING, WHITE);
		EndShaderMode();
	EndDrawing();
  }

  CloseWindow();

  return 0;
}
