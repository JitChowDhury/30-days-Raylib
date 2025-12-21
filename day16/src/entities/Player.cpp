#include "Player.h"
Player::Player()
{
  position = {
      GetScreenWidth() / 2.f,
      GetScreenHeight() / 2.f};
}

// handle inputs and collison each frame
void Player::Update(std::vector<std::unique_ptr<Enemy>> &enemies, std::vector<Bullet> &bullets)
{
  HandleInput(bullets);
  HandleEnemyCollision(enemies);
}
// movement input and bullet spawn
void Player::HandleInput(std::vector<Bullet> &bullets)
{
  Vector2 velocity{};

  if (IsKeyDown(KEY_W))
    velocity.y -= speed * GetFrameTime();
  if (IsKeyDown(KEY_S))
    velocity.y += speed * GetFrameTime();
  if (IsKeyDown(KEY_A))
    velocity.x -= speed * GetFrameTime();
  if (IsKeyDown(KEY_D))
    velocity.x += speed * GetFrameTime();

  position += velocity;

  position.x = Clamp(position.x, 0, GetScreenWidth() - size.x);
  position.y = Clamp(position.y, 0, GetScreenHeight() - size.y);

  fireTimer -= GetFrameTime();

  if (IsMouseButtonPressed(0) && fireTimer <= 0)
  {
    Bullet bullet;
    bullet.position = {position.x + size.x / 2, position.y + size.y / 2};
    bullet.velocity = Vector2Normalize(Vector2Subtract(GetMousePosition(), position));
    bullet.speed = bulletSpeed;
    bullet.damage = weaponDamage;
    bullet.color = bulletColor;

    bullets.push_back(bullet);
    fireTimer = fireCooldown;
  }
}
// enemy collision
void Player::HandleEnemyCollision(std::vector<std::unique_ptr<Enemy>> &enemies)
{
  for (auto &enemy : enemies)
  {
    Rectangle playerRec{position.x, position.y, size.x, size.y};

    if (CheckCollisionRecs(playerRec, enemy->IsActive() ? enemy->GetRect() : Rectangle{}))
    {
      if (invincibleTimer <= 0)
      {
        currentHp--;
        invincibleTimer = invincibleDuration;
      }
    }
  }

  if (invincibleTimer > 0)
  {
    invincibleTimer -= GetFrameTime();
    currentColor = invincibleColor;
  }
  else
  {
    currentColor = normalColor;
  }
}

void Player::Draw() const
{
  DrawRectangleV(position, size, currentColor);
}

void Player::Reset()
{
  currentHp = maxHp;
  invincibleTimer = invincibleDuration;
}
// weapom upgrade
void Player::ApplyUpgrade()
{
  weaponDamage = 5;
  bulletSpeed = 200.f;
  fireCooldown = 0.5f;
  bulletColor = BLUE;
}
