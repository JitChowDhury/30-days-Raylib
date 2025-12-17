#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include "Bullet.h"

enum class EnemyState
{
  Patrol,
  Chase
};

class Enemy
{
public:
  Enemy(float speed, float size);

  void Update(Vector2 playerPos, std::vector<Bullet> &bullets, int &score);
  void Draw() const;
  Rectangle GetRect();

  bool IsActive() const { return isActive; }

private:
  Vector2 position{};
  Rectangle collider{};
  Vector2 pointA{}, pointB{};

  float speed{0.f};
  float size{0.f};
  float chaseRange{100.f};

  int direction{1};
  int health{10};
  bool isActive{true};

  EnemyState state{EnemyState::Patrol};

  void Patrol();
  void Chase(Vector2 playerPos);
  bool HandleBulletCollision(std::vector<Bullet> &bullets, int &score);
};
