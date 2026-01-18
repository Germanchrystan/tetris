#include "game.h"
#include <raylib.h>
#include "constants.h"

Game::Game()
{
  grid = Grid();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
  score = 0;
  InitAudioDevice();
  music = LoadMusicStream("music.mp3");
  PlayMusicStream(music);
  rotateSound = LoadSound("Sounds/rotate.mp3");
  clearSound = LoadSound("Sounds/clar.mp3");
}

Game::~Game()
{
  UnloadSound(clearSound);
  UnloadSound(rotateSound);
  UnloadMusicStream(music);
  CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
  if (blocks.empty())
  {
    blocks = GetAllBlocks();
  }
  int randomIndex = rand() % blocks.size();
  Block block = blocks[randomIndex];
  blocks.erase(blocks.begin() + randomIndex);

  return block;
}

std::vector<Block> Game::GetAllBlocks()
{
  return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
  grid.Draw();
  currentBlock.Draw(GRID_MARGIN + 1, GRID_MARGIN + 1);
  switch(nextBlock.id)
  {
    case 3:
    nextBlock.Draw(255, 290);
    break;
    case 4:
    nextBlock.Draw(255,280);
    break;
    default:
    nextBlock.Draw(270, 270);
    break;
  }
}

void Game::MoveBlockLeft()
{
  currentBlock.Move(0,-1);  
  if(!IsBlockMovementAllowed())
  {
    currentBlock.Move(0,1);  
  }
}

void Game::MoveBlockRight()
{
  currentBlock.Move(0,1);
  if(!IsBlockMovementAllowed())
  {
    currentBlock.Move(0,-1);  
  }
}

void Game::MoveBlockDown()
{
  if (gameOver) return;
  currentBlock.Move(1,0);
  if(!IsBlockMovementAllowed())
  {
    currentBlock.Move(-1,0);
    LockBlock();
  }
}

void Game::HandleInput()
{
  int keyPressed = GetKeyPressed();
  if(gameOver)
  {
    if(keyPressed != 0)
    {
      gameOver = false;
      Reset();
    }
    return; // If the game is over, the user cannot move blocks
  }
  switch(keyPressed)
  {
    case KEY_LEFT:
    MoveBlockLeft();
    break;
    case KEY_RIGHT:
    MoveBlockRight();
    break;
    case KEY_DOWN:
    UpdateScore(0,1);
    MoveBlockDown();
    break;
    case KEY_SPACE:
    case KEY_UP:
    RotateBlock();
    break;
  }
}

void Game::RotateBlock()
{
  currentBlock.Rotate();
  if (!IsBlockMovementAllowed())
  {
    currentBlock.UndoRotation();
  }
  else
  {
    PlaySound(rotateSound);
  }
}

bool Game::IsBlockOutside()
{
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for(Position item: tiles)
  {
    if(grid.IsCellOutside(item.row, item.column))
    {
      return true;
    }
  }

  return false;
}

void Game::LockBlock()
{
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item: tiles)
  {
    grid.grid[item.row][item.column] = currentBlock.id;
  }
  currentBlock = nextBlock;
  if(!BlockFits())
  {
    gameOver = true;
  }
  nextBlock = GetRandomBlock();
  int rowsCleared = grid.ClearFullRows();
  if (rowsCleared > 0)
  {
    PlaySound(clearSound);
    UpdateScore(rowsCleared, 0);
  }
}

bool Game::BlockFits()
{
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item: tiles)
  {
    if(!grid.IsCellEmpty(item.row, item.column)) return false;
  }
  return true;
}

bool Game::IsBlockMovementAllowed()
{
  return !IsBlockOutside() && BlockFits();
}

void Game::Reset()
{
  grid.Initialize();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
  switch(linesCleared)
  {
    case 1:
    score += 100;
    break;
    case 2:
    score += 300;
    break;
    case 3:
    score += 500;
    break;
    default:
    break;
  }

  score += moveDownPoints;
}
