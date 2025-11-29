#include <iostream>
#include "raylib.h"

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
  if (IsKeyDown(KEY_A))
  {
    velocity.x -= speed;
  }
  if (IsKeyDown(KEY_D))
  {
    velocity.x += speed;
  }

  if (IsKeyUp(KEY_W) && IsKeyUp(KEY_S))
  {
    velocity.y = 0;
  }
  if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D))
  {
    velocity.x = 0;
  }
}

bool HandleCollision(Vector2 &position, int window_height, int window_width, float radius)
{
  bool isHitting = false;
  if (position.x + radius > window_width)
  {
    position.x = window_width - (radius);
    isHitting = true;
  }

  if (position.x - radius <= 0)
  {
    position.x = radius;
    isHitting = true;
  }
  if (position.y + radius > window_height)
  {
    position.y = window_height - (radius);
    isHitting = true;
  }
  if (position.y - radius <= 0)
  {
    position.y = radius;
    isHitting = true;
  }

  return isHitting;
}

int main()
{
  // Todays topic: AABB collisions (Axis Aligned Bounding Box)
  const int WINDOW_HEIGHT{600};
  const int WINDOW_WIDTH{600};

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Day 03");
  Vector2 position{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
  float radius{10.f};
  float speed{200.f};
  Color bg{WHITE};

  while (!WindowShouldClose())
  {

    Vector2 velocity{};
    //---------------Update----------------

    HandleInput(velocity, speed);
    bool hit = HandleCollision(position, WINDOW_HEIGHT, WINDOW_WIDTH, radius);

    std::cout << "Hitting Wall: " << std::boolalpha << hit << std::endl;
    if (hit)
    {
      bg = PURPLE;
    }
    else
    {
      bg = WHITE;
    }

    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();

    //---------------Drawing----------------
    BeginDrawing();
    ClearBackground(bg);

    DrawCircleGradient(position.x, position.y, radius, YELLOW, RED);
    EndDrawing();
  }
  CloseWindow();
}
