#include "block.h"
#include "colors.h"
#include "constants.h"
#define START_COL_POSITION 3
Block::Block()
{
  cellSize = 30;
  rotationState = 0;
  colors = GetCellColors();
  rowOffset = 0;
  colOffset = START_COL_POSITION;
}

void Block::Draw()
{
  std::vector<Position> tiles = GetCellPositions();
  for(Position item: tiles)
  {
    DrawRectangle(
      item.column * cellSize + GRID_MARGIN,
      item.row * cellSize + GRID_MARGIN,
      cellSize + 1,
      cellSize + 1,
      colors[id]);
  }
}

void Block::Rotate()
{
  rotationState++;
  if(rotationState == (int)cells.size())
  {
    rotationState = 0;
  }
}

void Block::UndoRotation()
{
  rotationState--;
  if (rotationState < 0)
  {
    rotationState = (int)cells.size() - 1;
  }
}

void Block::Move(int rows, int columns)
{
  rowOffset += rows;
  colOffset += columns;
}

std::vector<Position> Block::GetCellPositions()
{
  std::vector<Position> tiles = cells[rotationState];
  std::vector<Position> movedTiles;
  for(Position item: tiles)
  {
    Position newPos = Position(item.row + rowOffset, item.column + colOffset);
    movedTiles.push_back(newPos);
  }

  return movedTiles;
}
