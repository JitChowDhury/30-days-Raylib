// PLAYER:pos,speed,velocity
// BULLET:pos,velocity speed radius isactive
// ENEMY pos , Rectangele , speed , twopoints , isAlive
#include "raylib.h"
#include "raymath.h"
#include <cstdlib>
#include <ctime>
#include <vector>

struct Player
{
  Vector2 midPosition = {GetScreenWidth() / 2.f, GetScreenHeight() / 2.f};
  float playerWidth{20}, playerHeight{30};
  Vector2 playerPosition{midPosition.x - playerWidth, midPosition.y - playerHeight};
  Color playerColor{RED};

  float speed{200.f};

  void Update()
  {
    HandleInput();
    HandleCollision();
  }
  void HandleInput()
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

    playerPosition.x = Clamp(playerPosition.x, 0, GetScreenWidth() - playerWidth);
    playerPosition.y = Clamp(playerPosition.y, 0, GetScreenHeight() - playerHeight);

    playerPosition += velocity;
  }
  void HandleCollision()
  {
  }
};

struct Bullet
{
  Vector2 position{};
  Vector2 velocity{};
  float speed{100.f};
  bool isActive{true};
  float radius{5.f};

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

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "DAY 13 Game");

  //-----------------PLAYER---------------------->
  Player player;
  //-----------------BULLETS---------------------->
  std::vector<Bullet> bullets;
  while (!WindowShouldClose())
  {
    player.Update();
    if (IsMouseButtonPressed(0))
    {
      Bullet bullet;
      bullet.position = player.playerPosition;
      Vector2 dir = Vector2Normalize(Vector2Subtract(GetMousePosition(), player.playerPosition));
      bullet.velocity = dir;
      bullets.push_back(bullet);
    }

    for (auto &bullet : bullets)
    {
      bullet.Update();
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangleV(player.playerPosition, {player.playerWidth, player.playerHeight}, player.playerColor);
    for (auto &bullet : bullets)
    {
      DrawCircleV(bullet.position, bullet.radius, RED);
    }

    EndDrawing();
  }
}
