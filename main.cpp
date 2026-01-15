#include <raylib.h>
#include "game.h"
#include "constants.h"

double lastUpdateTime = 0;
float gameSpeed = GAME_INITIAL_SPEED;
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

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");
  SetTargetFPS(60);

  Game game = Game();

  while(!WindowShouldClose())
  {
    game.HandleInput();
    if (EventTriggered(gameSpeed))
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