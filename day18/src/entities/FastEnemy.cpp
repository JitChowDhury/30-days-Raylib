#include "FastEnemy.h"

FastEnemy::FastEnemy() : Enemy(220.f, 20.f, 2)
{
}

void FastEnemy::Draw() const
{
  DrawRectangleV(position, {size, size}, RED);
}
