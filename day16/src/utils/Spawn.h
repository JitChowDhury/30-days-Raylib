#pragma once
#include <vector>
#include "entities/Enemy.h"
#include "Utils.h"

// Spawns enemies and increases difficulty gradually
inline void SpawnEnemies(std::vector<Enemy> &enemies, int &count)
{
  for (int i = 0; i < count; i++)
  {
    enemies.emplace_back(100.f, GetRandomSize());
  }
  count += 2;
}
