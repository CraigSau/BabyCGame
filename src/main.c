#include "../raylib/src/raylib.h"
#include <stdio.h>

typedef struct {
  const char *text;
  int x;
  int y;
  int fontSize;
} PositionText;

enum GameScreen { TITLE_SCREEN, GAME_SCREEN, GAME_OVER_SCREEN };

void InitGame();
PositionText CalcTextSize(const char *text, int textWidth, int centerWidth,
                          int centerHeight, int fontSize);
void StartGame();

int main(void) {
  InitGame();
  return 0;
}

void InitGame() {
  enum GameScreen currentScreen = TITLE_SCREEN;

  InitWindow(0, 0, "Playin around");
  SetTargetFPS(120);

  // Get the screen sizes (must happen after init of window)
  const int screenWidth = GetScreenWidth();
  const int screenHeight = GetScreenHeight();
  const int centerWidth = screenWidth / 2;
  const int centerHeight = screenHeight / 2;

  const char *titleText = "Untitled";
  int titleFontSize = 40;

  PositionText titleTextPos =
      CalcTextSize(titleText, MeasureText(titleText, titleFontSize),
                   centerWidth, centerHeight, titleFontSize);

  const char *startText = "Start";
  int startFontSize = 30;
  int startTextWidth = MeasureText(startText, startFontSize);

  PositionText startTextPos = CalcTextSize(
      startText, startTextWidth, centerWidth, centerHeight + 80, startFontSize);

  Rectangle startButtonBounds = {startTextPos.x - 10, startTextPos.y - 5,
                                 startTextWidth + 20, startFontSize + 10};

  while (!WindowShouldClose()) {
    Vector2 mousePos = GetMousePosition();
    bool isHovering = CheckCollisionPointRec(mousePos, startButtonBounds);
    bool isClicked = isHovering && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (currentScreen == TITLE_SCREEN) {
      if (isClicked) {
        currentScreen = GAME_SCREEN;
      }
    }

    BeginDrawing();

    ClearBackground(BLACK);

    if (currentScreen == TITLE_SCREEN) {
      DrawText(titleTextPos.text, titleTextPos.x, titleTextPos.y,
               titleTextPos.fontSize, RAYWHITE);

      DrawText(startTextPos.text, startTextPos.x, startTextPos.y,
               startTextPos.fontSize, RAYWHITE);

      if (isHovering) {
        DrawRectangleLines(startButtonBounds.x, startButtonBounds.y,
                           startButtonBounds.width, startButtonBounds.height,
                           GREEN);
      }
    } else if (currentScreen == GAME_SCREEN) {
      StartGame();
    } else if (currentScreen == GAME_OVER_SCREEN) {
      DrawText("GAME OVER!", titleTextPos.x, titleTextPos.y,
               titleTextPos.fontSize, RAYWHITE);
    }

    EndDrawing();
    ClearBackground(BLACK);
  }

  CloseWindow();
}

void StartGame() {
  // TODO: Main Game loop here
}

PositionText CalcTextSize(const char *text, int textWidth, int centerWidth,
                          int centerHeight, int fontSize) {
  // Text for title screen
  PositionText textCalcd;
  textCalcd.text = text;
  textCalcd.fontSize = fontSize;
  textCalcd.x = centerWidth - (textWidth / 2);
  textCalcd.y = centerHeight - (textCalcd.fontSize / 2);

  return textCalcd;
}
