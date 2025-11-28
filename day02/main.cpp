#include "raylib.h"
#include "raymath.h"
#include "main.h"

int main()
{
  const int WINDOW_HEIGHT = 600;
  const int WINDOW_WIDTH = 600;

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Day 02 Game");
  Vector2 position{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
  float speed{100.f};

  while (!WindowShouldClose())
  {

    BeginDrawing();
    // Input
    Vector2 velocity{};
    HandleInput(velocity, speed);
    // update
    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();

    // Draw
    ClearBackground(WHITE);
    DrawCircle(position.x, position.y, 10, RED);
    EndDrawing();
  }

  CloseWindow();
}
void HandleInput(Vector2 &velocity, float speed)
{
  if (IsKeyDown(KEY_W))
  {
    velocity.y -= speed;
  }
  if (IsKeyDown(KEY_S))
  {
    velocity.y += speed;
  }
  if (IsKeyUp(KEY_W) && IsKeyUp(KEY_S))
  {
    velocity.y = 0;
  }

  if (IsKeyDown(KEY_A))
  {
    velocity.x -= speed;
  }

  if (IsKeyDown(KEY_D))
  {
    velocity.x += speed;
  }
  if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D))
  {
    velocity.x = 0;
  }
}