#include "raylib.h"

int main()
{
  const int WINDOW_HEIGHT{600};
  const int WINDOW_WIDTH{600};

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Day 03");

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RED);
    EndDrawing();
  }
  CloseWindow();
}
