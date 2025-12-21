#include "TankyEnemy.h"

TankyEnemy::TankyEnemy() : Enemy(80.f, 45.f, 6)
{
}

void TankyEnemy::Draw() const
{
  DrawRectangleV(position, {size, size}, RED);
}
