#include "core/Game.h"
#include "raylib.h"
#include "utils/Spawn.h"

Game::Game()
{
  SpawnEnemies();
}

void Game::Run()
{
  while (!WindowShouldClose())
  {
    if (IsKeyPressed(KEY_F11))
      ToggleBorderlessWindowed();

    Update();
    Draw();
  }
}

void Game::Update()
{
  player.Update(enemies, bullets);

  // Enemy wave logic
  if (enemies.empty())
  {
    if (waveTimer > 0.f)
      waveTimer -= GetFrameTime();
    else
    {
      SpawnEnemies();
      waveTimer = waveDelay;
    }
  }

  // Enemy update & cleanup
  for (auto it = enemies.begin(); it != enemies.end();)
  {
    if (!it->IsActive())
      it = enemies.erase(it);
    else
    {
      it->Update(player.GetPosition(), bullets, score);
      ++it;
    }
  }

  // Weapon upgrade
  if (IsKeyPressed(KEY_N) && !upgradeApplied)
  {
    player.ApplyUpgrade();
    upgradeApplied = true;
  }

  // Bullet update
  for (auto &bullet : bullets)
  {
    if (bullet.isActive)
      bullet.Update();
  }

  // Player death
  if (player.GetHealth() <= 0)
  {
    Reset();
  }
}
// draw everything on screen
void Game::Draw()
{
  BeginDrawing();
  ClearBackground(RAYWHITE);

  player.Draw();

  for (auto &enemy : enemies)
    enemy.Draw();

  for (auto &bullet : bullets)
    if (bullet.isActive)
      DrawCircleV(bullet.position, bullet.radius, bullet.color);

  DrawText(TextFormat("Score: %d", score), 40, 40, 24, BLACK);
  DrawText(TextFormat("Health: %d", player.GetHealth()), 40, 70, 24, BLACK);

  EndDrawing();
}
// enemies spawn
void Game::SpawnEnemies()
{
  for (int i = 0; i < enemyCount; i++)
  {
    enemies.emplace_back(100.f, GetRandomSize());
  }
  enemyCount += 2;
}
// game erset
void Game::Reset()
{
  score = 0;
  enemyCount = 1;
  enemies.clear();
  bullets.clear();
  SpawnEnemies();
  player.Reset();
}
