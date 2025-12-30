#pragma once
#include <vector>
#include <memory>

#include "entities/Player.h"
#include "entities/Enemy.h"
#include "entities/Bullet.h"

class Game
{
public:
  Game();

  void Run();

private:
  // Game objects
  Player player;
  // std::vector<Enemy> enemies;
  std::vector<std::unique_ptr<Enemy>> enemies;
  std::vector<Bullet> bullets;

  // Game state
  int score{0};
  int enemyCount{1};

  float waveDelay{2.5f};
  float waveTimer{waveDelay};

  bool upgradeApplied{false};

  void Update();
  void Draw();
  void SpawnEnemies();
  void Reset();
};
