#include "raylib.h"
#include "raymath.h"

#include <iostream>
#include <vector>
using namespace std;

struct Bullet
{
  Vector2 position{};
  Vector2 velocity{};
  float radius;
  float speed;
  bool isActive;

  void Update()
  {

    position.x += velocity.x * speed * GetFrameTime();
    position.y += velocity.y * speed * GetFrameTime();
  }
};

int main()
{
  const int WINDOW_WIDTH{600};
  const int WINDOW_HEIGHT{600};
  SetTargetFPS(60);

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "DAY 06");
  Rectangle player{550, 250, 20, 40};
  std::vector<Bullet> bullets;
  while (!WindowShouldClose())
  {

    if (IsMouseButtonPressed(0))
    {

      Vector2 mouse = GetMousePosition();

      Vector2 direction = Vector2Subtract(mouse, {player.x, player.y});

      direction = Vector2Normalize(direction);

      Bullet bullet{
          {player.x, player.y},
          direction,
          5.f,
          200,
          true};

      bullets.push_back(bullet);
    }

    for (auto it = bullets.begin(); it != bullets.end();)
    {
      Bullet &bullet = (*it);
      bullet.Update();
      if ((bullet.position.x - bullet.radius < 0) || (bullet.position.x > GetScreenWidth()) || (bullet.position.y - bullet.radius < 0) || (bullet.position.y + bullet.radius > GetScreenHeight()))
      {
        it = bullets.erase(it);
        std::cout << "Outside , DELETING.... , Size Now" << bullets.size() << std::endl;
      }
      else
      {
        it++;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangleRec(player, RED);
    for (Bullet &bullet : bullets)
    {
      DrawCircle(bullet.position.x, bullet.position.y, bullet.radius, RED);
    }
    // DrawCircle(bullet.position.x, bullet.position.y, bullet.radius, RED);
    EndDrawing();
  }

  CloseWindow();
}