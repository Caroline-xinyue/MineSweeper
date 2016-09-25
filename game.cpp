#include "game.h"

using namespace std;

/*
  Destructor for Game.
 */
Game::~Game() {
  delete board;
  delete level;
}

/*
  Constructor for Game
 */
Game::Game(int myLevel) {
  Running = true;
  if(myLevel == 1) {
    level = new Level("Intermediate", 16, 16, 40);
  } else if(myLevel == 2) {
    level = new Level("Expert", 30, 16, 99);
  } else {
    level = new Level("Beginner", 8, 8, 10);
  }
  board = new Board(level);
  winState = NONE;
}

/*
  Method called by the main method in main.cpp that initilize the board, and execute the game while Running is true.
 */
int Game::OnExecute() {
  if(board -> OnInit() == false) {
    std::cout << "Init failure" << std::endl;
    return -1;
  }

  SDL_Event Event;

  while(Running) {
    while(SDL_PollEvent(&Event)) {
      OnEvent(&Event);
    }
    checkWin();
    if(winState == LOSE) {
      board -> OnRender(LOSE);
    } else if(winState == WIN) {
      board -> OnRender(WIN);
    }else {
      board -> OnRender(NONE);
    }
  }
  return 0;
}

/*
  Method to reset the game by calling reset in board.
*/
void Game::reset() {
  board -> reset();
  winState = NONE;
}

/*
  Method to check the win state of the game.
 */
// Must marked all the cells that are not bomb
void Game::checkWin() {
  if(board -> getNumBomb() + board -> getNumMarked() == board -> getNumTotal()) {
    winState = WIN;
  }
}
