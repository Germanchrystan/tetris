#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
  private:
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    bool IsBlockOutside();
    void LockBlock();
    bool BlockFits();
    bool IsBlockMovementAllowed();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
    void MoveBlockLeft();
    void MoveBlockRight();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    Grid grid;

  public:
    Game();
    ~Game();
    void HandleInput();
    void RotateBlock();
    void UndoRotation();
    void Draw();
    void MoveBlockDown();
    bool gameOver;
    int score;
    Music music;
    Sound rotateSound;
    Sound clearSound;
};