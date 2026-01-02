#pragma once
#include <vector>
#include <memory>
#include "World.h"

class Game
{
public:
  Game();

  void Run();

private:
  World world;
  void Update();
  void Draw();
};
