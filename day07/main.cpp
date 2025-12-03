#include "raylib.h"
#include "raymath.h"
#include <iostream>
using namespace std;

struct Enemy
{
  Vector2 position; //{x,y}
  float speed;
  float size;
  float chaseDistance;
};

void HandleInput(Vector2 &playerPos, float speed)
{
  Vector2 velocity{};
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

  playerPos.x += velocity.x * GetFrameTime();
  playerPos.y += velocity.y * GetFrameTime();
}

void HandleCollision(Vector2 &playerPos)
{
  playerPos.x = Clamp(playerPos.x, 0.f, static_cast<float>(GetScreenWidth()) - 40.f);
  playerPos.y = Clamp(playerPos.y, 0.f, static_cast<float>(GetScreenHeight()) - 40.f);
}

int main()
{
  const int WINDOW_WIDTH{600};
  const int WINDOW_HEIGHT{600};

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Day 07 Game");

  //---------------------Player-------------------
  Vector2 playerPosition{WINDOW_WIDTH / 2 - 20, WINDOW_HEIGHT / 2 - 20};
  float speed{200.f};
  Vector2 velocity{};

  //---------------------Enemy-------------------
  Enemy enemy{{200, 200}, 100.f, 20.f, 100.f};
  // Rectangle player{playerPosition.x, playerPosition.y, 40, 40};
  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    HandleInput(playerPosition, speed);
    HandleCollision(playerPosition);

    Vector2 distance = playerPosition - enemy.position;
    if (Vector2Length(distance) < enemy.chaseDistance)
    {
      Vector2 direction = Vector2Normalize(distance);
      enemy.speed = 100.f;
      enemy.position += direction * enemy.speed * GetFrameTime();
    }
    else
    {
      enemy.speed = 0.f;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawCircle(enemy.position.x, enemy.position.y, enemy.size, RED);
    DrawRectangle(playerPosition.x, playerPosition.y, 40, 40, ORANGE);

    EndDrawing();
  }

  return 0;
}