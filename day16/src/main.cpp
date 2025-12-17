#include "raylib.h"
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

#include "entities/Player.h"
#include "entities/Enemy.h"
#include "entities/Bullet.h"
#include "utils/Utils.h"
#include "utils/Spawn.h"

int main()
{
  srand((unsigned int)time(nullptr));

  const int WINDOW_WIDTH = 600;
  const int WINDOW_HEIGHT = 600;

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "DAY 16 - Refactored");
  SetTargetFPS(60);

  // ---------------- Game Objects ----------------
  Player player;
  std::vector<Bullet> bullets;
  std::vector<Enemy> enemies;

  // ---------------- Game State ----------------
  int score = 0;
  int enemyCount = 1;

  float waveDelay = 2.5f;
  float waveTimer = waveDelay;

  bool upgradeApplied = false;

  SpawnEnemies(enemies, enemyCount);

  // ---------------- Main Loop ----------------
  while (!WindowShouldClose())
  {
    if (IsKeyPressed(KEY_F11))
      ToggleBorderlessWindowed();

    // ----------- Update -----------
    player.Update(enemies, bullets);

    // Enemy wave logic
    if (enemies.empty())
    {
      if (waveTimer > 0.f)
        waveTimer -= GetFrameTime();
      else
      {
        SpawnEnemies(enemies, enemyCount);
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

    // Weapon upgrade (same logic as before)
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

    // Player death reset
    if (player.GetHealth() <= 0)
    {
      score = 0;
      enemyCount = 1;
      enemies.clear();
      bullets.clear();
      SpawnEnemies(enemies, enemyCount);
      player.Reset();
    }

    // ----------- Draw -----------
    BeginDrawing();
    ClearBackground(RAYWHITE);

    player.Draw();

    for (const auto &enemy : enemies)
      enemy.Draw();

    for (const auto &bullet : bullets)
      if (bullet.isActive)
        DrawCircleV(bullet.position, bullet.radius, bullet.color);

    DrawText(TextFormat("Score: %d", score), 40, 40, 24, BLACK);
    DrawText(TextFormat("Health: %d", player.GetHealth()), 40, 70, 24, BLACK);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
