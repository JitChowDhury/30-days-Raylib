#include "raylib.h"
#include "core/Game.h"

int main()
{
  InitWindow(600, 600, "DAY 16");
  SetTargetFPS(60);

  Game game;
  game.Run();

  CloseWindow();
  return 0;
}
