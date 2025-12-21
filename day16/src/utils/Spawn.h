#pragma once
#include <memory>
#include <vector>

#include <raylib.h>
#include "entities/Enemy.h"
#include "entities/FastEnemy.h"
#include "entities/TankyEnemy.h"
#include "Utils.h"
// Spawns enemies and increases difficulty gradually
inline void SpawnEnemy(std::vector<std::unique_ptr<Enemy>> &enemies, int &count)
{

  for (int i = 0; i < count; i++)
  {

    int random_choice = GetRandomValue(0, 100);
    if (random_choice < 60)
    {
      enemies.push_back(std::make_unique<FastEnemy>());
    }
    else
    {
      enemies.push_back(std::make_unique<TankyEnemy>());
    }
  }
  count += 2;
}
