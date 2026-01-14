#include <stdio.h>
#include "grid.h"
#include "colors.h"

Grid::Grid() 
{
  numRows = 20;
  numCols = 10;
  cellSize = 30;
  Initialize();
  colors = GetCellColors();
}

void Grid::Initialize() 
{
  for (int i = 0; i < numRows; ++i) 
  {
    for (int j = 0; j < numCols; ++j) 
    {
      grid[i][j] = 0;
    }
  }
}

void Grid::Print() 
{
  for (int i = 0; i < numRows; ++i) 
  {
    for (int j = 0; j < numCols; ++j) 
    {
      printf("%d ", grid[i][j]);
    }
    printf("\n");
  }
}

void Grid::Draw()
{
  for (int i = 0; i < numRows; ++i) 
  {
    for (int j = 0; j < numCols; ++j) 
    {
      int cellValue = grid[i][j];
      DrawRectangle(j * cellSize+1, i * cellSize+1, cellSize-1, cellSize-1, colors[cellValue]);
    }
  }
}