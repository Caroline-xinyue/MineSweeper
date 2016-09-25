#include "game.h"
#include "time.h"

/*
  Method to handle SDL events.
 */
void Game::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

/*
  Method to exit the program.
 */
void Game::OnExit() {
  Running = false;
}

/*
  Method to handle the left-button-down event, here specifically handles the reset event for the topbar and calls LButtonClicked to check game winState.
 */
void Game::OnLButtonDown(int mX, int mY) {
  int gridSize = board -> getGridSize();
  int topbarH = board -> getTopbarH();
  int width = board -> getWidth();
  if(mX >= width/2*gridSize - topbarH/2 && mX <= width/2*gridSize + topbarH/2 && mY >= 0 && mY <= topbarH) {
    reset();
    return;
  }
  if(mY <= topbarH) {
    return;
  }

  int col = mX/gridSize;
  int row = (mY-topbarH)/gridSize;
  bool lose = board->LButtonClicked(row, col);
  if(lose) {
    winState = LOSE;
  }
}

/*
  Method to handle the right-button-down event, here specifically handles the reset event for the topbar and calls RButtonClicked.
 */
void Game::OnRButtonDown(int mX, int mY) {
  int gridSize = board -> getGridSize();
  int topbarH = board -> getTopbarH();
  if(mY <= topbarH) {
    return;
  }
  int col = mX/gridSize;
  int row = (mY - topbarH)/gridSize;
  board->RButtonClicked(row, col);
}
