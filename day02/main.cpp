#include "raylib.h"

int main()
{
  const int WINDOW_HEIGHT = 600;
  const int WINDOW_WIDTH = 600;

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Day 02 Game");

  while (!WindowShouldClose())
  {

    BeginDrawing();
    ClearBackground(WHITE);

    EndDrawing();
  }

  CloseWindow();
}