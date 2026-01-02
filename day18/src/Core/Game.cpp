#include "Game.h"

Game::Game()
{
}

void Game::Run()
{
  InitWindow(600, 600, "Day 18");
  while (!WindowShouldClose())
  {
    Update();
    Draw();
  }
}
void Game::Update()
{
}
void Game::Draw()
{
  BeginDrawing();
  ClearBackground(SKYBLUE);
  world.Draw();
  EndDrawing();
}