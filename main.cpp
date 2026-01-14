#include <raylib.h>
#include "game.h"

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
  double currentTime = GetTime();
  if(currentTime - lastUpdateTime >= interval)
  {
    lastUpdateTime = currentTime;
    return true;
  }
  return false;
}

int main()
{
  Color darkGreen = Color{44, 44, 127, 255};

  const int screenWidth = 300;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Tetris");
  SetTargetFPS(60);

  Game game = Game();

  while(!WindowShouldClose())
  {
    game.HandleInput();
    if (EventTriggered(0.2))
    {
      game.MoveBlockDown();
    }
    BeginDrawing();
    ClearBackground(darkGreen);
    game.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}