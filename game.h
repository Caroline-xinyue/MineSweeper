#ifndef _GAME_H_
#define _GAME_H_

#include <string>
#include <iostream>
#include "SDL/SDL.h"
#include "board.h"
#include "CEvent.h"

using namespace std;

class Game : public CEvent {
 private:
  bool Running;
  Level* level = NULL;
  Board* board = NULL;
  int winState;
  enum {
    NONE = 0,
    WIN,
    LOSE,
  };
 public:
  ~Game();
  Game(int iSize);
  int OnExecute();
  void OnLoop();
  void reset();
  void OnEvent(SDL_Event* Event);
  void OnExit();
  void OnLButtonDown(int mX, int mY);
  void OnRButtonDown(int mX, int mY);
  void checkWin();

  // AI
  void AI();
  int countFreeSquares(int row, int col);
  int countFlags(int row, int col);
  void flagBombs();
  void setFlag(int, int);
  void setMark(int, int);
  void randomMark();
  int countNeighbors(int row, int col);
  int randomGenerator(int limit);
  void render();
  
};

#endif
