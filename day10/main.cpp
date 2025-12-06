#include "raylib.h"
#include "raymath.h"

#include <vector>
#include <string>

enum State
{
  PATROL,
  CHASE,
};
struct Enemy
{
  // patrol points
  Vector2 pointA;
  Vector2 pointB;
  // Enemy Datas
  Vector2 position;
  float size{};
  float speed{};
  float baseSpeed{};

  // patrol behaviour
  int direction{+1};
  float idleDuration{2.f};
  float idleTimer{0.f};

  float chaseRange{100.f};

  State state{PATROL};

  Enemy(Vector2 a, Vector2 b, float s = 20.f, float _speed = 100.f) : pointA(a), pointB(b), size(s), speed(_speed), baseSpeed(_speed)
  {
    position = pointA;
  }

  void Update(Vector2 playerPos)
  {
    float dt = GetFrameTime();
    // if distance to player is less than the chaseRange enemy will chase the player

    float distance = Vector2Distance(position, playerPos);

    state = (distance < chaseRange) ? CHASE : PATROL;

    switch (state)
    {
    case PATROL:
      Patrol(dt, distance);
      break;
    case CHASE:
      Chase(playerPos, dt);
      speed = baseSpeed;
      break;
    };
  }

  void Patrol(float dt, float distance)
  {
    position.x += direction * speed * dt;

    if (position.x >= pointB.x)
    {
      HandleIdleState(-1, dt, distance);
    }
    else if (position.x <= pointA.x)
    {
      HandleIdleState(+1, dt, distance);
    }
  }

  void HandleIdleState(int newDirection, float dt, float distance)
  {
    if (distance < chaseRange)
    {
      state = CHASE;
      speed = baseSpeed;
      return;
    }

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

  bool IsOutsideScreen()
  {
    if (position.x + radius < 0 || position.x - radius > GetScreenWidth() || position.y + radius < 0 || position.y - radius > GetScreenHeight())
    {
      return true;
    }
    return false;
  }

  bool IsEnemyCollisin(std::vector<Enemy> &enemies, int &score)
  {
    for (auto it = enemies.begin(); it != enemies.end();)
    {
      Enemy &enemy = *it;
      if (CheckCollisionCircleRec(position, radius, Rectangle{enemy.position.x, enemy.position.y, enemy.size, enemy.size}))
      {
        it = enemies.erase(it);
        score += 10;
        return true;
      }
      else
      {
        ++it;
      }
    }
    return false;
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
  int score{0};
  //------------ENEMY----------------
  std::vector<Enemy> enemies;

  enemies.emplace_back(Vector2{100, 100}, Vector2{300, 100}, 10.f);
  enemies.emplace_back(Vector2{200, 300}, Vector2{500, 300}, 20.f);
  enemies.emplace_back(Vector2{50, 400}, Vector2{250, 400}, 12.f);

  //------------BULLETS---------------

  std::vector<Bullet> bullets;

  while (!WindowShouldClose())
  {

    if (IsMouseButtonPressed(0))
    {
      Vector2 mousePos = GetMousePosition();
      Vector2 direction = Vector2Normalize(Vector2Subtract(mousePos, playerPos));
      Bullet bullet{
          playerPos,
          direction,
          5.f,
          200,
          true};

      bullets.push_back(bullet);
    }

    for (auto it = bullets.begin(); it != bullets.end();)
    {
      Bullet &bullet = *it;
      bullet.Update();
      if (bullet.IsOutsideScreen() || bullet.IsEnemyCollisin(enemies, score))
      {
        it = bullets.erase(it);
      }
      else
      {
        ++it;
      }
    }

    HandleInput(playerPos, playerSpeed, playerSize);

    for (auto &enemy : enemies)
    {
      enemy.Update(playerPos);
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawRectangleV(playerPos, {playerSize, playerSize}, ORANGE);

    for (auto &enemy : enemies)
    {
      DrawRectangleV(enemy.position, {enemy.size, enemy.size}, RED);
    }

    for (auto &bullet : bullets)
    {
      DrawCircleV(bullet.position, bullet.radius, PURPLE);
    }
    std::string message = "Score: " + std::to_string(score);
    DrawText(message.c_str(), 40, 40, 24, BLACK);

    EndDrawing();
  }

  CloseWindow();
}