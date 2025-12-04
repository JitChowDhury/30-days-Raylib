#include <iostream>
#include "raylib.h"
#include "raymath.h"
using namespace std;

enum Behaviour
{
  patrol,
  chase,
};

struct Enemy
{
  Vector2 position;
  Rectangle rec{position.x, position.y, 40, 20};
  float speed{100.f};

  int patrolDirection{1};
  Behaviour behaviour;
  float chaseDistance{100.f};
  Vector2 pointA{90, 90};
  Vector2 pointB{400, 90};

  void Update(Vector2 playerPos)
  {
    float distance = Vector2Distance(playerPos, position);
    if (distance < chaseDistance)
    {
      behaviour = Behaviour::chase;
    }
    else
    {
      behaviour = Behaviour::patrol;
    }

    if (behaviour == chase)
    {
      Vector2 direction = playerPos - position;
      direction = Vector2Normalize(direction);
      position.x += direction.x * speed * GetFrameTime();
      position.y += direction.y * speed * GetFrameTime();
    }
    else if (behaviour == patrol)
    {
      position.x += patrolDirection * speed * GetFrameTime();
      if (position.x <= pointA.x)
      {
        patrolDirection = +1;
      }
      else if (position.x >= pointB.x)
      {
        patrolDirection = -1;
      }
    }
  }
};

int main()
{
  const int WINDOW_WIDTH{600};
  const int WINDOW_HEIGHT{600};

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Day 08 game");
  Vector2 playerPos{100, 100};
  float speed = 200.f;
  float size = 40.f;
  Vector2 velocity{};
  Enemy enemy;

  enemy.position.x = enemy.pointA.x;
  enemy.position.y = enemy.pointA.y;

  while (!WindowShouldClose())
  {
    Vector2 velocity{};
    if (IsKeyDown(KEY_W))
    {
      velocity.y -= speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_S))
    {
      velocity.y += speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_A))
    {
      velocity.x -= speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_D))
    {
      velocity.x += speed * GetFrameTime();
    }

    playerPos += velocity;

    playerPos.x = Clamp(playerPos.x, 0, GetScreenWidth() - size);
    playerPos.y = Clamp(playerPos.y, 0, GetScreenHeight() - size);

    enemy.Update(playerPos);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawLine(enemy.pointA.x, enemy.pointA.y, enemy.pointB.x, enemy.pointB.y, BLUE);
    DrawRectangle(playerPos.x, playerPos.y, size, size, PURPLE);
    DrawRectangle(enemy.position.x, enemy.position.y, 20, 20, RED);

    EndDrawing();
  }
}