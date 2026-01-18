#include <iostream>
#include <raylib.h>
#include "game.h"
#include "constants.h"
#include "colors.h"

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

  Font font = LoadFontEx("monogram.ttf", 64, 0, 0);
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
    DrawTextEx(font, "Score", {365,15}, 38, 2, WHITE);
    DrawTextEx(font, "Next", { 370, 175}, 38, 2, WHITE);
    // Score
    char scoreText[10];
    snprintf(scoreText, sizeof(scoreText), "%d", game.score);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
    if(game.gameOver)
    {
      DrawTextEx(font, "Game Over!", {320,450}, 38, 2, WHITE);
    }
    DrawRectangleRounded({320,55,170,60}, 0.3, 6, lightBlue);
    DrawRectangleRounded({320,215,170,180}, 0.3, 6, lightBlue);
    DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
    game.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}