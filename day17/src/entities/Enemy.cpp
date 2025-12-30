
#include "Enemy.h"
#include <cstdlib>

static Vector2 GetRandomPosition(float size)
{
  float x = size + rand() % (int)(GetScreenWidth() - size * 2);
  float y = size + rand() % (int)(GetScreenHeight() - size * 2);
  return {x, y};
}
// constructor
// Choose tow random position and if pointA is greater then swaps also sets the rectangle  to position
Enemy::Enemy(float spd, float sz, int hp)
    : speed(spd), size(sz), health(hp)
{
  pointA = GetRandomPosition(size);
  pointB = GetRandomPosition(size);

  if (pointA.x > pointB.x)
    std::swap(pointA, pointB);

  position = pointA;
  collider = {position.x, position.y, size, size};
}

// changes state based on distance between player and enemy
// also sets active flag to false if health = 0;
void Enemy::Update(Player &player, std::vector<Bullet> &playerBullets, int &score, std::vector<Bullet> &enemyBullets)
{
  if (!isActive)
    return;

  HandleBulletCollision(playerBullets, score);
  HandlePlayerBulletCollision(player, enemyBullets);

  float distance = Vector2Distance(position, player.GetPosition());
  state = (distance < chaseRange) ? EnemyState::Chase : EnemyState::Patrol;

  if (state == EnemyState::Patrol)
    Patrol();
  else
    Chase(player.GetPosition(), enemyBullets);

  collider.x = position.x;
  collider.y = position.y;

  if (health <= 0)
    isActive = false;
}
// patrol state
void Enemy::Patrol()
{
  position.x += direction * speed * GetFrameTime();

  if (position.x >= pointB.x)
    direction = -1;
  if (position.x <= pointA.x)
    direction = 1;
}
// chase player if distance is less that chase distance
void Enemy::Chase(Vector2 playerPos, std::vector<Bullet> &enemyBullets)
{
  Vector2 dir = Vector2Normalize(Vector2Subtract(playerPos, position));
  position.x += dir.x * speed * GetFrameTime();
  position.y += dir.y * speed * GetFrameTime();
  fireTimer -= GetFrameTime();
  if (fireTimer <= 0)
  {
    Bullet bullet;
    bullet.position = {position.x + size / 2, position.y + size / 2};
    bullet.velocity = Vector2Normalize(Vector2Subtract(playerPos, position));
    bullet.speed = 50.f;
    bullet.damage = 1.f;
    bullet.color = MAGENTA;

    enemyBullets.push_back(bullet);
    fireTimer = fireCoolDown;
  }
}
void Enemy::HandlePlayerBulletCollision(Player &player, std::vector<Bullet> &bullets)
{
  for (auto it = bullets.begin(); it != bullets.end();)
  {
    if (CheckCollisionCircleRec(it->position, it->radius, player.GetPlayerRec()))
    {
      it->isActive = false;
      it = bullets.erase(it);
      player.Damage(.5f);
    }
    else
    {
      ++it;
    }
  }
}
// loops through the bullet list and checks if any bullet touches enemy , if it does then remove that bullet
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

// Draw the enemy on screen
// void Enemy::Draw() const
// {
//   DrawRectangleV(position, {size, size}, ORANGE);
// }
