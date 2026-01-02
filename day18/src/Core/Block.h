#include "raylib.h"

enum BLOCKTYPE
{
  AIR,
  GRASS,
  DIRT,
  STONE,

};

class Block
{
private:
  Rectangle rec;
  Color color;
  BLOCKTYPE type;

public:
  Block(float x, float y, float width, float height, int surfaceHeight);
  Color GetColor();
  void Draw();
};
