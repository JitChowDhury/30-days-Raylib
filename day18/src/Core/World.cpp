#include "World.h"

World::World()
{
  for (int y{0}; y < coloumns; y++)
  {
    for (int x{0}; x < rows; x++)
    {
      tiles.emplace_back(Block{
          x * (float)tileSize,
          y * (float)tileSize,
          (float)tileSize,
          (float)tileSize,
          surfaceHeight});
    }
  }
}

void World::Draw()
{

  for (auto &block : tiles)
  {
    block.Draw();
  }
}