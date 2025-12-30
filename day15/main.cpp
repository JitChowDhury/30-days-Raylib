// PLAYER:pos,speed,velocity
// BULLET:pos,velocity speed radius isactive
// ENEMY pos , Rectangele , speed , twopoints , isAlive
#include "raylib.h"
#include "raymath.h"
#include <iostream>
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
  float speed{};
  bool isActive{true};
  float radius{5.f};
  float damage;
  Color color{};

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
  int health{10};

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

    if (health <= 0)
    {
      isActive = false;
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

        health -= (*it).damage;
        it = bullets.erase(it);
        score += 10;
        // isActive = false;
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
  Vector2 originalPosition{midPosition.x - playerWidth, midPosition.y - playerHeight};
  Vector2 playerPosition{originalPosition};
  Color originalColor{PURPLE};
  Color invincibleColor{BLACK};
  Color playerColor{originalColor};
  float speed{200.f};

  int maxHp = 10;
  int currentHp = maxHp;
  float invincibleTimer{};
  float invincibleDuration{0.7f};

  // weapon stat
  int weaponDamage{2};
  float fireCoolDown{1.f};
  float fireTimer{0};
  float bulletSpeed{100.f};
  Color bulletColor{RED};

  void Update(std::vector<Enemy> &enemies)
  {
    HandleInput();
    HandleCollision(enemies);
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
  void HandleCollision(std::vector<Enemy> &enemies)
  {

    for (auto &it : enemies)
    {
      if (CheckCollisionRecs({playerPosition.x, playerPosition.y, playerWidth, playerHeight}, {it.Rec}))
      {
        if (invincibleTimer <= 0)
        {
          currentHp -= 1;
          invincibleTimer = invincibleDuration;
        }
      }
    }

    if (invincibleTimer > 0)
    {
      invincibleTimer -= GetFrameTime();
      playerColor = invincibleColor;
    }
    else
    {
      playerColor = originalColor;
    }
  }

  void Reset()
  {
    playerPosition = originalPosition;
    playerColor = originalColor;
    currentHp = maxHp;
    invincibleTimer = invincibleDuration;
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
  std::vector<Bullet> playerBullets;
  //-----------------ENEMY---------------------->

  std::vector<Enemy> enemies;
  int numEnemies = 1;
  SpawnEnemy(enemies, numEnemies);
  //----------------SCORESYSTEM------------------->
  float waitTimer = 2.5f;
  float actualTimer = waitTimer;
  int score = 0;
  //-----------------WEAPON SYSTEM------------------>
  bool isUpgradeApplied{false};
  //-----------------MAIN LOOP----------->
  while (!WindowShouldClose())
  {

    if (IsKeyPressed(KEY_F11))
    {
      ToggleBorderlessWindowed();
    }

    player.Update(enemies);
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
    if (IsKeyPressed(KEY_N) && isUpgradeApplied == false)
    {
      player.weaponDamage = 5.f;
      player.bulletSpeed = 200.f;
      isUpgradeApplied = true;
      player.bulletColor = BLUE;
      player.fireCoolDown = .5f;
    }

    if (IsMouseButtonPressed(0) && player.fireTimer <= 0)
    {
      Bullet bullet;
      bullet.position = {player.playerPosition.x + player.playerWidth / 2, player.playerPosition.y + player.playerHeight / 2};
      Vector2 dir = Vector2Normalize(Vector2Subtract(GetMousePosition(), player.playerPosition));
      bullet.velocity = dir;
      bullet.damage = player.weaponDamage;
      bullet.speed = player.bulletSpeed;
      bullet.color = player.bulletColor;
      bullets.push_back(bullet);
      player.fireTimer = player.fireCoolDown;
    }

    player.fireTimer -= GetFrameTime();

    for (auto &bullet : bullets)
    {
      if (bullet.isActive)
      {
        bullet.Update();
      }
    }

    if (player.currentHp <= 0)
    {
      score = 0;
      numEnemies = 0;
      enemies.clear();
      bullets.clear();
      SpawnEnemy(enemies, numEnemies);
      player.Reset();
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
        DrawCircleV(bullet.position, bullet.radius, bullet.color);
      }
    }

    std::string message = "Score: " + std::to_string(score);
    std::string healthMessage = "Health " + std::to_string(player.currentHp);
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2) << actualTimer;
    std::string timerMessage = "Timer: " + ss.str();
    DrawText(message.c_str(), 40, 40, 24, BLACK);
    DrawText(healthMessage.c_str(), 40, 70, 24, BLACK);
    DrawText(timerMessage.c_str(), GetScreenWidth() - 200, 40, 24, BLACK);

    EndDrawing();
  }
}
