
#pragma once
#include "raylib.h"
#include <vector>
#include "Enemy.h"
#include "Bullet.h"
#include <memory>

class Player
{
public:
  Player();

  void Update(std::vector<std::unique_ptr<Enemy>> &enemies, std::vector<Bullet> &bullets);
  void Draw() const;
  void Reset();
  void ApplyUpgrade();
  Vector2 GetPosition() const { return position; }
  int GetHealth() const { return currentHp; }

private:
  Vector2 position{};
  Vector2 size{20.f, 30.f};

  float speed{200.f};

  int maxHp{10};
  int currentHp{10};

  float invincibleTimer{0.f};
  float invincibleDuration{0.7f};

  // Weapon
  int weaponDamage{2};
  float fireCooldown{1.f};
  float fireTimer{0.f};
  float bulletSpeed{100.f};

  Color normalColor{PURPLE};
  Color invincibleColor{BLACK};
  Color currentColor{PURPLE};
  Color bulletColor{RED};

  void HandleInput(std::vector<Bullet> &bullets);
  void HandleEnemyCollision(std::vector<std::unique_ptr<Enemy>> &enemies);
};
