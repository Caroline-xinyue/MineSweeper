#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <iostream>
#include "SDL/SDL.h"
#include "level.h"
#include "CSurface.h"

using namespace std;

class Board {
 private:
  // declare SDL surfaces
  SDL_Surface* Surf_Display;
  SDL_Surface* Surf_Grid;
  SDL_Surface* Surf_0;
  SDL_Surface* Surf_1;
  SDL_Surface* Surf_2;
  SDL_Surface* Surf_3;
  SDL_Surface* Surf_4;
  SDL_Surface* Surf_5;
  SDL_Surface* Surf_6;
  SDL_Surface* Surf_7;
  SDL_Surface* Surf_8;
  SDL_Surface* Surf_Bomb;
  SDL_Surface* Surf_BombClicked;
  SDL_Surface* Surf_Flag;
  SDL_Surface* Surf_FlagError;

  SDL_Surface* Surf_Win;
  SDL_Surface* Surf_Lose;
  SDL_Surface* Surf_Restart;
 private:
  // define the Grid struct for the board
  struct Grid {
    int cell;
    bool isBomb;
    bool isBombClicked;
    bool isMarked;
    bool isFlagged;
    Grid() {
      cell = -1;
      isBomb = false;
      isBombClicked = false;
      isMarked = false;
      isFlagged = false;
    }
  };

  // board properties
  int width;
  int height;
  int gridSize = 40;
  Grid** grid;
  int numBomb;
  int numMarked;
  int numTotal;
  int topbarH = 75;
  
 public:
  // Destructor
  ~Board();
  
  // Constructor
  Board(Level* level);

  // getters and setters
  int getWidth();
  int getHeight();
  int getGridSize();
  int getNumBomb();
  int getNumTotal();
  int getNumMarked();
  int getGridCount(int row, int col);
  int getTopbarH();
  bool isGridMarked(int row, int col);
  bool isGridFlagged(int row, int col);
  bool isGridBomb(int row, int col);
  void setFlagState(int row, int col, bool flagState);
  void setGridMarked(int row, int col);
  void setHintRegion(int row, int col);
  void setBombClicked(int row, int col);

  // member functions
  bool OnInit();
  void setAITestBoard();
  void initBomb();
  void reset();
  int countNeighbors(int row, int col);
  void OnRender(int winState);
  void renderTopbar(int winState);
  void renderBoard();
  void OnRenderMarked(int X, int Y, int count);
  bool LButtonClicked(int mX, int mY);
  void RButtonClicked(int mX, int mY);
  void incrementNumMarked();
};

int randomGenerator(int limit);

#endif
