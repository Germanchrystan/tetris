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

  public:
    Grid grid;
    Game();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    void HandleInput();
    void RotateBlock();
    void UndoRotation();
    void Draw();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
};