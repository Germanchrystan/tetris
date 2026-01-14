#include <raylib.h>
#include "grid.h"

int main()
{
  Color darkGreen = Color{44, 44, 127, 255};

  const int screenWidth = 300;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Tetris");
  SetTargetFPS(60);

  Grid grid = Grid();
  // grid.Print();

  while(!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(darkGreen);

    grid.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}