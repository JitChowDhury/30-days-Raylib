// PLAYER:pos,speed,velocity
// BULLET:pos,velocity speed radius isactive
// ENEMY pos , Rectangele , speed , twopoints , isAlive
#include "raylib.h"
#include "raymath.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

enum State
{
  PATROL,
  CHASE,
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

  bool IsOutsideScreen()
  {
    if (position.x + radius < 0 || position.x - radius > GetScreenWidth() || position.y + radius < 0 || position.y - radius > GetScreenHeight())
    {
      isActive = false;
    }
    isActive = true;
  }
};
Vector2 GetRandomPosition(float size)
{

  // min+rand()%max-min+1;
  float posX = size + rand() % static_cast<int>((GetScreenWidth() - size) - size + 1);
  float posy = size + rand() % static_cast<int>((GetScreenHeight() - size) - size + 1);

  return {posX, posy};
}
struct Enemy
{
  Vector2 position{};
  Vector2 velocity{};
  float chaseRange{100.f};
  int direction{+1};
  bool isActive{true};

  float speed;
  float size;
  Rectangle Rec;

  Vector2 pointA;
  Vector2 pointB;

  State currentState{PATROL};

  Enemy(float _speed, float _size) : speed(_speed), size(_size)
  {
    pointA = GetRandomPosition(size);
    pointB = GetRandomPosition(size);
    if (pointA.x > pointB.x)
    {
      std::swap(pointA, pointB);
    }
    position = pointA;

    Rec = Rectangle{position.x, position.y, size, size};
  }

  void Update(Vector2 playerPos, std::vector<Bullet> &bullets, int &score)
  {
    if (CheckCollision(bullets, score))
    {
      return;
    }
    float distance = Vector2Distance(position, playerPos);

    currentState = (distance < chaseRange) ? CHASE : PATROL;

    switch (currentState)
    {
    case PATROL:
      position.x += direction * speed * GetFrameTime();

      if (position.x >= pointB.x)
      {
        PatrolState(-1);
      }
      else if (position.x <= pointA.x)
      {
        PatrolState(+1);
      }

      break;

    case CHASE:
      ChaseState(playerPos);
      break;
    }
  }

  void PatrolState(int newDirection)
  {
    direction = newDirection;
  }

  void ChaseState(Vector2 playerPos)
  {
    Vector2 direction = Vector2Subtract(playerPos, position);
    direction = Vector2Normalize(direction);

    position.x += direction.x * speed * GetFrameTime();
    position.y += direction.y * speed * GetFrameTime();
  }

  bool CheckCollision(std::vector<Bullet> &bullets, int &score)
  {
    Rec.x = position.x;
    Rec.y = position.y;

    for (auto it = bullets.begin(); it != bullets.end();)
    {
      if (CheckCollisionCircleRec(it->position, it->radius, Rec))
      {

        it = bullets.erase(it);
        score += 10;
        isActive = false;
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

struct Player
{
  Vector2 midPosition = {GetScreenWidth() / 2.f, GetScreenHeight() / 2.f};
  float playerWidth{20}, playerHeight{30};
  Vector2 playerPosition{midPosition.x - playerWidth, midPosition.y - playerHeight};
  Color playerColor{PURPLE};

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

float GetrandomSize()
{
  return static_cast<float>(10 + rand() % (50 - 10 + 1));
}

void SpawnEnemy(std::vector<Enemy> &enemies, int &numOfEnemies)
{
  for (int i = 0; i < numOfEnemies; i++)
  {
    Enemy enemy{100.f, GetrandomSize()};
    enemies.push_back(enemy);
  }
  numOfEnemies += 2;
}
int main()
{

  srand(time(0));
  const int WINDOW_WIDTH{600};
  const int WINDOW_HEIGHT{600};

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "DAY 13 Game");

  //-----------------PLAYER---------------------->
  Player player;
  //-----------------BULLETS---------------------->
  std::vector<Bullet> bullets;
  //-----------------ENEMY---------------------->

  std::vector<Enemy> enemies;
  int numEnemies = 1;
  SpawnEnemy(enemies, numEnemies);
  //----------------SCORESYSTEM------------------->
  float waitTimer = 2.5f;
  float actualTimer = waitTimer;
  int score = 0;
  //-----------------MAIN LOOP----------->
  while (!WindowShouldClose())
  {

    player.Update();
    if (enemies.size() == 0)
    {
      if (actualTimer > 0.f)
      {
        actualTimer -= GetFrameTime();
      }
      else
      {
        SpawnEnemy(enemies, numEnemies);
        actualTimer = waitTimer;
      }
    }

    for (auto it = enemies.begin(); it != enemies.end();)
    {
      if ((*it).isActive == false)
      {
        it = enemies.erase(it);
      }
      else
      {
        (*it).Update(player.playerPosition, bullets, score);
        ++it;
      }
    }

    if (IsMouseButtonPressed(0))
    {
      Bullet bullet;
      bullet.position = {player.playerPosition.x + player.playerWidth / 2, player.playerPosition.y + player.playerHeight / 2};
      Vector2 dir = Vector2Normalize(Vector2Subtract(GetMousePosition(), player.playerPosition));
      bullet.velocity = dir;
      bullets.push_back(bullet);
    }

    for (auto &bullet : bullets)
    {
      if (bullet.isActive)
      {
        bullet.Update();
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangleV(player.playerPosition, {player.playerWidth, player.playerHeight}, player.playerColor);
    for (auto &enemy : enemies)
    {
      if (enemy.isActive)
      {
        DrawRectangleV(enemy.position, {enemy.size, enemy.size}, ORANGE);
      }
    }

    for (auto &bullet : bullets)
    {
      if (bullet.isActive)
      {
        DrawCircleV(bullet.position, bullet.radius, RED);
      }
    }

    std::string message = "Score: " + std::to_string(score);
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2) << actualTimer;
    std::string timerMessage = "Timer: " + ss.str();
    DrawText(message.c_str(), 40, 40, 24, BLACK);
    DrawText(timerMessage.c_str(), 400, 40, 24, BLACK);

    EndDrawing();
  }
}
