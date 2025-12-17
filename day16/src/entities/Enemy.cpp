
#include "Enemy.h"
#include <cstdlib>

static Vector2 GetRandomPosition(float size)
{
  float x = size + rand() % (int)(GetScreenWidth() - size * 2);
  float y = size + rand() % (int)(GetScreenHeight() - size * 2);
  return {x, y};
}

Enemy::Enemy(float spd, float sz)
    : speed(spd), size(sz)
{
  pointA = GetRandomPosition(size);
  pointB = GetRandomPosition(size);

  if (pointA.x > pointB.x)
    std::swap(pointA, pointB);

  position = pointA;
  collider = {position.x, position.y, size, size};
}

void Enemy::Update(Vector2 playerPos, std::vector<Bullet> &bullets, int &score)
{
  if (HandleBulletCollision(bullets, score))
    return;

  float distance = Vector2Distance(position, playerPos);
  state = (distance < chaseRange) ? EnemyState::Chase : EnemyState::Patrol;

  if (state == EnemyState::Patrol)
    Patrol();
  else
    Chase(playerPos);

  collider.x = position.x;
  collider.y = position.y;

  if (health <= 0)
    isActive = false;
}

void Enemy::Patrol()
{
  position.x += direction * speed * GetFrameTime();

  if (position.x >= pointB.x)
    direction = -1;
  if (position.x <= pointA.x)
    direction = 1;
}

void Enemy::Chase(Vector2 playerPos)
{
  Vector2 dir = Vector2Normalize(Vector2Subtract(playerPos, position));
  position.x += dir.x * speed * GetFrameTime();
  position.y += dir.y * speed * GetFrameTime();
}

bool Enemy::HandleBulletCollision(std::vector<Bullet> &bullets, int &score)
{
  for (auto it = bullets.begin(); it != bullets.end();)
  {
    if (CheckCollisionCircleRec(it->position, it->radius, collider))
    {
      health -= it->damage;
      it = bullets.erase(it);
      score += 10;
      return true;
    }
    else
    {
      ++it;
    }
  }
  return false;
}

void Enemy::Draw() const
{
  DrawRectangleV(position, {size, size}, ORANGE);
}

Rectangle Enemy::GetRect()
{
  return collider;
}