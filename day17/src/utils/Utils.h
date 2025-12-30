#pragma once
#include "raylib.h"
#include <cstdlib>

// Returns a random position inside the screen bounds,
// keeping the entity fully visible.
inline Vector2 GetRandomPosition(float size)
{
  float x = size + rand() % (int)(GetScreenWidth() - size * 2);
  float y = size + rand() % (int)(GetScreenHeight() - size * 2);
  return {x, y};
}

// Random enemy size between 10 and 50
inline float GetRandomSize()
{
  return static_cast<float>(10 + rand() % (50 - 10 + 1));
}
