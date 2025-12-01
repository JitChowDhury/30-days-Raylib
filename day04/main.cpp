#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

struct Rec
{
  Rectangle rec;
  Color color;
  bool isCollected;
};

void HandleInput(Vector2 &velocity, float speed)
{

  velocity = {0.f, 0.f};
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

void HandleCollision(Vector2 &position, float radius, std::vector<Rec> &obstacles, int &score)
{
  // HANDLE WINDOW COLLISION

  if (position.x + radius > GetScreenWidth())
  {
    position.x = GetScreenWidth() - radius;
  }
  if (position.x - radius < 0.f)
  {
    position.x = radius;
  }
  if (position.y + radius > GetScreenHeight())
  {
    position.y = GetScreenHeight() - radius;
  }
  if (position.y - radius < 0)
  {
    position.y = radius;
  }
  bool spawnNew = false;
  for (auto it = obstacles.begin(); it != obstacles.end();)
  {
    Rectangle rec = (*it).rec;
    Color realColor = (*it).color;

    if (CheckCollisionCircleRec(position, radius, (*it).rec))
    {
      (*it).isCollected = true;
      it = obstacles.erase(it);
      spawnNew = true;
      score += 10;
    }
    else
    {
      ++it;
    }
  }

  if (spawnNew)
  {
    obstacles.emplace_back(Rec{
        {static_cast<float>((rand()) % (GetScreenWidth() - 200)), static_cast<float>((rand()) % (GetScreenHeight() - 200)), 40, 20},
        {static_cast<unsigned char>(rand() % 255),
         static_cast<unsigned char>(rand() % 255),
         static_cast<unsigned char>(rand() % 255),
         255},
        false});
  }
}

int main()
{

  const int WINDOW_WIDTH = 600;
  const int WINDOW_HEIGHT = 600;
  Color color{WHITE};
  Vector2 position{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
  float speed{200.f};
  float radius{10.f};
  Vector2 velocity{};
  std::vector<Rec> obstacles;
  int score{0};

  int x = time(0);
  srand(x);

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Day 04 Game");
  std::cout << rand() << std::endl;

  for (int i = 0; i < 5; i++)
  {
    obstacles.emplace_back(Rec{
        {static_cast<float>((rand()) % (GetScreenWidth() - 200)), static_cast<float>((rand()) % (GetScreenHeight() - 200)), 40, 20},
        {static_cast<unsigned char>(rand() % 255),
         static_cast<unsigned char>(rand() % 255),
         static_cast<unsigned char>(rand() % 255),
         255},
        false});
  }

  while (!WindowShouldClose())
  {

    //------------------------UPDATE----------------------
    HandleInput(velocity, speed);

    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();
    HandleCollision(position, radius, obstacles, score);
    //-------------------------DRAW------------------------
    BeginDrawing();
    ClearBackground(color);

    for (auto &obj : obstacles)
    {
      if (!obj.isCollected)
      {
        DrawRectangleRec(obj.rec, obj.color);
      }
    }
    DrawCircleGradient(position.x, position.y, radius, YELLOW, RED);
    std::string message = "Score: " + std::to_string(score);

    DrawText(message.c_str(), 20, 20, 16, BLACK);

    EndDrawing();
  }

  CloseWindow();
}
