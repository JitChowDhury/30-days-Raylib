#include <iostream>
#include <vector>
#include "raylib.h"
#include "raymath.h"

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

const float PLAYER_SPEED = 200.f;
const float ENEMY_SPEED = 100.f;

const float CHASE_RANGE = 150.f;
const float WANDER_MIN_TIME = 1.0f;
const float WANDER_MAX_TIME = 3.0f;

enum Behaviour
{
  patrol,
  chase,
  wander
};

struct Enemy
{
  Rectangle rec;
  float speed;

  Behaviour behaviour;

  int patrolDirection;
  Vector2 pointA;
  Vector2 pointB;
  Vector2 wanderDirection;
  float wanderTimer;
};

float Distance(Vector2 a, Vector2 b)
{
  return Vector2Distance(a, b);
}

Vector2 GetRandomDirection()
{
  float x = GetRandomValue(-100, 100) / 100.f;
  float y = GetRandomValue(-100, 100) / 100.f;

  return Vector2Normalize({x, y});
}

int main()
{

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Day 05 game");

  Vector2 playerPos = {300, 400};
  Vector2 playerVelocity = {0, 0};

  const float PLAYER_SIZE = 20;

  std::vector<Enemy> enemies;

  Enemy e;
  e.rec = {50, 50, 20, 20};
  e.speed = ENEMY_SPEED;

  e.behaviour = patrol;
  e.patrolDirection = 1;
  e.pointA = {50, 50};
  e.pointB = {WINDOW_WIDTH - 50, 50};
  e.wanderDirection = {1, 0};
  e.wanderTimer = 2.0f;

  enemies.push_back(e);

  while (!WindowShouldClose())
  {
    float dt = GetFrameTime();

    playerVelocity = {0, 0};
    if (IsKeyDown(KEY_W))
      playerVelocity.y -= PLAYER_SPEED;
    if (IsKeyDown(KEY_S))
      playerVelocity.y += PLAYER_SPEED;
    if (IsKeyDown(KEY_A))
      playerVelocity.x -= PLAYER_SPEED;
    if (IsKeyDown(KEY_D))
      playerVelocity.x += PLAYER_SPEED;

    playerPos.x += playerVelocity.x * dt;
    playerPos.y += playerVelocity.y * dt;

    for (Enemy &enemy : enemies)
    {
      Vector2 enemyPos = {enemy.rec.x, enemy.rec.y};
      float dist = Distance(enemyPos, playerPos);

      if (dist < CHASE_RANGE)
      {
        enemy.behaviour = chase;
      }
      else
      {
        enemy.behaviour = patrol;
      }

      if (enemy.behaviour == patrol)
      {
        enemy.rec.x += enemy.patrolDirection * enemy.speed * dt;

        if (enemy.rec.x >= enemy.pointB.x)
        {
          enemy.patrolDirection = -1;
        }
        else if (enemy.rec.x <= enemy.pointA.x)
        {
          enemy.patrolDirection = +1;
        }
      }
      else if (enemy.behaviour == chase)
      {
        Vector2 direction = Vector2Normalize(playerPos - enemyPos);
        enemy.rec.x += direction.x * enemy.speed * dt;
        enemy.rec.y += direction.y * enemy.speed * dt;
      }
      else if (enemy.behaviour == wander)
      {
        enemy.wanderTimer -= dt;

        if (enemy.wanderTimer <= 0)
        {
          enemy.wanderDirection = GetRandomDirection();
          enemy.wanderTimer = GetRandomValue(WANDER_MIN_TIME * 100,
                                             WANDER_MAX_TIME * 100) /
                              100.0f;
        }

        enemy.rec.x += enemy.wanderDirection.x * enemy.speed * dt;
        enemy.rec.y += enemy.wanderDirection.y * enemy.speed * dt;
      }
    }
    playerPos.x = Clamp(playerPos.x, 0, WINDOW_WIDTH - PLAYER_SIZE);
    playerPos.y = Clamp(playerPos.y, 0, WINDOW_HEIGHT - PLAYER_SIZE);

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawRectangle(playerPos.x, playerPos.y, PLAYER_SIZE, PLAYER_SIZE, BLUE);

    for (Enemy &enemy : enemies)
    {
      Color c = RED;
      if (enemy.behaviour == chase)
        c = PURPLE;
      if (enemy.behaviour == wander)
        c = YELLOW;

      DrawRectangleRec(enemy.rec, c);
    }

    DrawText("Player = BLUE", 10, 10, 20, DARKGRAY);
    DrawText("Enemy Patrol = RED", 10, 30, 20, DARKGRAY);
    DrawText("Enemy Chase = PURPLE", 10, 50, 20, DARKGRAY);
    DrawText("Enemy WANDER = YELLOW", 10, 70, 20, DARKGRAY);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}