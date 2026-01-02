#pragma once
#include "Enemy.h"

class TankyEnemy : public Enemy
{
public:
  TankyEnemy();
  void Draw() const override;
};