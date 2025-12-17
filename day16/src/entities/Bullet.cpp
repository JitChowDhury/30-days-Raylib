#include "Bullet.h"

void Bullet::Update()
{
  position.x += velocity.x * speed * GetFrameTime();
  position.y += velocity.y * speed * GetFrameTime();

  if (IsOutsideScreen())
    isActive = false;
}

bool Bullet::IsOutsideScreen() const
{
  return position.x + radius < 0 ||
         position.x - radius > GetScreenWidth() ||
         position.y + radius < 0 ||
         position.y - radius > GetScreenHeight();
}
