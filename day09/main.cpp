#include "raylib.h"
#include "raymath.h"

enum State
{
  PATROL,
  CHASE,
};

struct Enemy
{
  Vector2 pointA{100, 100};
  Vector2 pointB{500, 100};
  Vector2 enemyPosition = {pointA.x, pointA.y};
  float size{20.f};
  float speed{100.f};
  float actualSpeed{100.f};
  Rectangle rec{enemyPosition.x, enemyPosition.y, size, size};
  float chaseRange{100.f};
  int patrolDirection{+1};
  float idleTimer = 2.f;
  float timer{0.f};

  State state{PATROL};

  void Update(Vector2 playerPos)
  {
    // if distance to player is less than the chaseRange enemy will chase the player

    float distance = Vector2Distance(enemyPosition, playerPos);

    if (distance < chaseRange)
    {
      state = CHASE;
    }
    else
    {
      state = PATROL;
    }

    switch (state)
    {
    case PATROL:
      enemyPosition.x += patrolDirection * speed * GetFrameTime();
      if (enemyPosition.x >= pointB.x)
      {
        if (timer > idleTimer)
        {
          patrolDirection = -1;
          timer = 0;
          speed = actualSpeed;
        }
        else
        {
          timer += GetFrameTime();
          speed = 0.f;
        }
      }
      else if (enemyPosition.x <= pointA.x)
      {
        if (timer > idleTimer)
        {
          patrolDirection = +1;
          timer = 0;
          speed = actualSpeed;
        }
        else
        {
          timer += GetFrameTime();
          speed = 0.f;
        }
      }

      break;

    case CHASE:
      Vector2 direction = Vector2Subtract(playerPos, enemyPosition);
      direction = Vector2Normalize(direction);

      enemyPosition.x += direction.x * speed * GetFrameTime();
      enemyPosition.y += direction.y * speed * GetFrameTime();

      break;
    }
  }
};

void HandleInput(Vector2 &playerPos, float speed, float playerSize)
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

  playerPos.x = Clamp(playerPos.x, 0, GetScreenWidth() - playerSize);
  playerPos.y = Clamp(playerPos.y, 0, GetScreenHeight() - playerSize);
}

int main()
{
  const int WINDOW_WIDTH{600};
  const int WINDOW_HEIGHT{600};

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Day 09 Game");

  //-----------------PLAYER--------------

  float speed{200.f};
  float playerSize{40.f};
  Vector2 playerPos{WINDOW_WIDTH / 2 - playerSize, WINDOW_HEIGHT / 2 - playerSize};

  Enemy enemy{20, 100.f};

  while (!WindowShouldClose())
  {

    HandleInput(playerPos, speed, playerSize);
    enemy.Update(playerPos);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawRectangle(playerPos.x, playerPos.y, playerSize, playerSize, ORANGE);
    DrawRectangle(enemy.enemyPosition.x, enemy.enemyPosition.y, enemy.size, enemy.size, RED);

    EndDrawing();
  }

  CloseWindow();
}