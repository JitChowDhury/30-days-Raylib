#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include "Bullet.h"
#include "Player.h"

enum class EnemyState
{
  Patrol,
  Chase
};
class Player;
class Enemy
{
public:
  virtual ~Enemy() = default;
  virtual void Update(Player &player, std::vector<Bullet> &playerBullets, int &score, std::vector<Bullet> &enemyBullets);
  virtual void Draw() const = 0;

  Rectangle GetRect() const { return collider; }

  bool IsActive() const { return isActive; }

protected:
  Enemy(float speed, float size, int health);
  Vector2 position{};
  Rectangle collider{};
  Vector2 pointA{}, pointB{};

  float speed{0.f};
  float size{0.f};
  float chaseRange{100.f};
  float fireCoolDown{2.f};
  float fireTimer{0.f};

  int direction{1};
  int health{10};
  bool isActive{true};

  EnemyState state{EnemyState::Patrol};

  void Patrol();
  void Chase(Vector2 playerPos, std::vector<Bullet> &enemyBullets);
  bool HandleBulletCollision(std::vector<Bullet> &bullets, int &score);
  void HandlePlayerBulletCollision(Player &player, std::vector<Bullet> &bullets);
};
