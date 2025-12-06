#include "raylib.h"
#include "raymath.h"

enum State
{
  PATROL,
  CHASE,
};

struct Enemy
{
  // patrol points
  Vector2 pointA{100, 100};
  Vector2 pointB{500, 500};
  // Enemy Datas
  Vector2 position{pointA.x, pointA.y};
  float size{20.f};
  float speed{100.f};
  float baseSpeed{speed};

  // patrol behaviour
  int direction{+1};
  float idleDuration{2.f};
  int idleTimer{};

  float chaseRange{100.f};

  State state{PATROL};

  void Update(Vector2 playerPos)
  {
    float dt = GetFrameTime();
    // if distance to player is less than the chaseRange enemy will chase the player

    float distance = Vector2Distance(position, playerPos);

    state = (distance < chaseRange) ? CHASE : PATROL;

    switch (state)
    {
    case PATROL:
      Patrol(dt);
      break;
    case CHASE:
      Chase(playerPos, dt);
      break;
    };
  }

  void Patrol(float dt)
  {
    position.x += direction * speed * dt;

    if (position.x >= pointB.x)
    {
      HandleIdleState(-1, dt);
    }
  }

  void HandleIdleState(int newDirection, float dt)
  {

    if (idleTimer >= idleDuration)
    {
      direction = newDirection;
      speed = baseSpeed;
      idleTimer = 0.f;
    }
    else
    {
      idleTimer += dt;
      speed = 0.f;
    }
  }

  void Chase(Vector2 playerPos, float dt)
  {
    Vector2 direction = Vector2Normalize(Vector2Subtract(playerPos, position));
    position.x += direction.x * speed * dt;
    position.y += direction.y * speed * dt;
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

  // playerPos += velocity
  playerPos = Vector2Add(playerPos, velocity);

  playerPos.x = Clamp(playerPos.x, 0, GetScreenWidth() - playerSize);
  playerPos.y = Clamp(playerPos.y, 0, GetScreenHeight() - playerSize);
}

int main()
{
  const int WINDOW_WIDTH{600};
  const int WINDOW_HEIGHT{600};

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Day 09 Game");

  //-----------------PLAYER--------------

  float playerSpeed{200.f};
  float playerSize{40.f};
  Vector2 playerPos{WINDOW_WIDTH / 2 - playerSize, WINDOW_HEIGHT / 2 - playerSize};

  Enemy enemy;

  while (!WindowShouldClose())
  {

    HandleInput(playerPos, playerSpeed, playerSize);
    enemy.Update(playerPos);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawRectangleV(playerPos, {playerSize, playerSize}, ORANGE);
    DrawRectangleV(enemy.position, {enemy.size, enemy.size}, RED);

    EndDrawing();
  }

  CloseWindow();
}