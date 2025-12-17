#pragma once
#include "raylib.h"

// Represents a single projectile fired by the player
class Bullet
{
public:
  Vector2 position{};
  Vector2 velocity{};
  float speed{0.f};
  float radius{5.f};
  float damage{0.f};
  bool isActive{true};
  Color color{RED};

  void Update();
  bool IsOutsideScreen() const;
};
