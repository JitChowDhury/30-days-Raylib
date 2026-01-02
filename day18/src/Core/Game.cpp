#include "core/Game.h"
#include "raylib.h"
#include "utils/Spawn.h"
#include "entities/FastEnemy.h"
#include "entities/TankyEnemy.h"

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
  player.Update(enemies, playerBullets);

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
    if (!(*it)->IsActive())
      it = enemies.erase(it);
    else
    {
      (*it)->Update(player, playerBullets, score, enemyBullets);
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
  for (auto &bullet : playerBullets)
  {
    if (bullet.isActive)
      bullet.Update();
  }
  for (auto &bullet : enemyBullets)
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
    enemy->Draw();

  for (auto &bullet : playerBullets)
    if (bullet.isActive)
      DrawCircleV(bullet.position, bullet.radius, bullet.color);
  for (auto &bullet : enemyBullets)
    if (bullet.isActive)
      DrawCircleV(bullet.position, bullet.radius, bullet.color);

  DrawText(TextFormat("Score: %d", score), 40, 40, 24, BLACK);
  DrawText(TextFormat("Health: %.1f", player.GetHealth()), 40, 70, 24, BLACK);

  EndDrawing();
}
// enemies spawn
void Game::SpawnEnemies()
{
  SpawnEnemy(enemies, enemyCount);
  enemyCount += 2;
}
// game erset
void Game::Reset()
{
  score = 0;
  enemyCount = 1;
  enemies.clear();
  playerBullets.clear();
  SpawnEnemies();
  player.Reset();
}
