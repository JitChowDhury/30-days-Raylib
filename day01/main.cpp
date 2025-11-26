#include "raylib.h"

int main()
{
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Basic Window");

  Vector2 playerPosition{(float)screenWidth / 2 - 40, (float)screenHeight / 2 - 40};

  float speed{};
  float walkSpeed{200.0f};
  float runSpeed{500.0f};

  Color recColor;

  SetTargetFPS(60);

  while (!WindowShouldClose()) // detect window close button or ESC key
  {
    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
      speed = runSpeed;
    }
    else
    {
      speed = walkSpeed;
    }

    if (IsKeyDown(KEY_SPACE))
    {
      recColor = RED;
    }
    else
    {
      recColor = VIOLET;
    }

    //--------------Update-----------
    if (IsKeyDown(KEY_W))
      playerPosition.y -= speed * GetFrameTime();
    if (IsKeyDown(KEY_S))
      playerPosition.y += speed * GetFrameTime();
    if (IsKeyDown(KEY_A))
      playerPosition.x -= speed * GetFrameTime();
    if (IsKeyDown(KEY_D))
      playerPosition.x += speed * GetFrameTime();
    //--------------Draw-------------

    if (playerPosition.x + 40 > screenWidth || playerPosition.x < 0.f || playerPosition.y < 0.f || playerPosition.y + 40 > screenHeight)
    {
      playerPosition.x = (float)screenWidth / 2 - 40;
      playerPosition.y = (float)screenHeight / 2 - 40;
    }

    BeginDrawing();
    ClearBackground(WHITE);

    DrawRectangle(playerPosition.x, playerPosition.y, 40, 40, recColor);
    DrawText("Use WASD to move", (float)screenWidth / 2 - 40, 20.f, 25, RED);

    EndDrawing();
  }
  CloseWindow();

  return 0;
}