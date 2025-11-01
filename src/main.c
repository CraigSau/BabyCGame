#include "../raylib/src/raylib.h"

int main(void)
{
  const int screenWidth = 400;
  const int screenHeight = 400;

  InitWindow(screenWidth, screenHeight, "Test Window Raylib");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawText("Achievement unlocked, first window!", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
