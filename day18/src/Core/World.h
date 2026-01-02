#pragma once
#include <vector>
#include "raylib.h"
#include "Block.h"

class World
{
private:
  int width{600};
  int height{600};
  int surfaceHeight{12};
  int tileSize{32};
  int rows{width / tileSize};
  int coloumns{height / tileSize};
  std::vector<Block> tiles;

public:
  World();
  void Draw();
};