#pragma once
#include "Enemy.h"

class FastEnemy : public Enemy
{
public:
  FastEnemy();
  void Draw() const override;
};