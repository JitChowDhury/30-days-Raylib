#include "Block.h"

Block::Block(float x, float y, float width, float height, int surfaceTileY)
{
  rec = {x, y, width, height};

  int tileY = static_cast<int>(y / height);

  if (tileY < surfaceTileY)
    type = AIR;
  else if (tileY == surfaceTileY)
    type = GRASS;
  else if (tileY <= surfaceTileY + 2)
    type = DIRT;
  else
    type = STONE;
}

Color Block::GetColor()
{
  if (type == BLOCKTYPE::AIR)
  {
    return Color{0, 0, 0, 0};
  }
  else if (type == BLOCKTYPE::GRASS)
  {
    return GREEN;
  }
  else if (type == BLOCKTYPE::DIRT)
  {
    return BROWN;
  }
  else
  {
    return GRAY;
  }
}

void Block::Draw()
{
  DrawRectangleRec(rec, GetColor());
}
