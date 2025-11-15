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
void StartGame(Camera camera);
void InitMap(float heights[], Vector3 positions[], Color colors[]);

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

  Camera camera = {0};
  camera.position = (Vector3){0.2f, 0.4f, 0.2f};
  camera.target = (Vector3){0.185f, 0.4f, 0.0f};
  camera.up = (Vector3){0.0f, 0.1f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;
  int cameraMode = CAMERA_FIRST_PERSON;

  // Generates some random columns just to see some shit on the screen
  float heights[10] = {0};
  Vector3 positions[10] = {0};
  Color colors[10] = {0};

  for (int i = 0; i < 10; i++) {
    heights[i] = (float)GetRandomValue(1, 12);
    positions[i] = (Vector3){(float)GetRandomValue(-15, 15), heights[i] / 2.0f,
                             (float)GetRandomValue(-15, 15)};
    colors[i] =
        (Color){GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255};
  }

  // GAME LOOP
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

    ClearBackground(BLANK);

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
      BeginMode3D(camera);

      InitMap(heights, positions, colors);

      StartGame(camera);

      EndMode3D();
    } else if (currentScreen == GAME_OVER_SCREEN) {
      DrawText("GAME OVER!", titleTextPos.x, titleTextPos.y,
               titleTextPos.fontSize, RAYWHITE);
    }

    EndDrawing();
    ClearBackground(BLACK);
  }

  CloseWindow();
}

void GameLoop() {}

void StartGame(Camera camera) {
  // TODO: Main Game loop here
  ClearBackground(RAYWHITE);

  UpdateCamera(&camera, CAMERA_FIRST_PERSON);
}

void InitMap(float heights[], Vector3 positions[], Color colors[]) {
  // Draw some cubes around
  for (int i = 0; i < 10; i++) {
    DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
    DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
  }

  DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f},
            LIGHTGRAY); // Draw ground
  DrawCube((Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f,
           BLUE); // Draw a blue wall
  DrawCube((Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f,
           LIME); // Draw a green wall
  DrawCube((Vector3){0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f,
           GOLD); // Draw a yellow wall
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
