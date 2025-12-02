#include <iostream>
#include "raylib.h"
#include "raymath.h"

int main()
{
  const int WINDOW_WIDTH{600};
  const int WINDOW_HEIGHT{600};

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Day 05 Game");
  Vector2 position{};
  Vector2 velocity{};
  Vector2 pointA{50, 50};
  Vector2 pointB{WINDOW_WIDTH - 50, 50};
  float speed{200.f};
  int direction{1};
  position = pointA;
  Rectangle rec{position.x, position.y, 20, 20};

  while (!WindowShouldClose())
  {
    // UPDATE
    velocity = {0, 0};
    if (position.x >= pointB.x && direction == 1)
    {

      direction = -1;
    }
    else if (position.x <= pointA.x && direction == -1)
    {
      direction = 1;
    }

    position.x += direction * speed * GetFrameTime();

    BeginDrawing();
    ClearBackground(WHITE);
    DrawRectangle(position.x, position.y, 20, 20, RED);
    EndDrawing();
  }
  CloseWindow();
}