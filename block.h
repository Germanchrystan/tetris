#pragma once
#include<vector>
#include<map>
#include "position.h"
#include "colors.h"

class Block
{
  private:
  int cellSize;
  int rotationState;
  int rowOffset;
  int colOffset;
  std::vector<Color> colors;

  public:
    Block();
    void Move(int rows, int columns);
    std::vector<Position> GetCellPositions();
    void Draw(int offsetX, int offsetY);
    int id;
    std::map<int,std::vector<Position>> cells;
    void Rotate();
    void UndoRotation();
};