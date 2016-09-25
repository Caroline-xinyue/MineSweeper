#include "game.h"

using namespace std;

/*
  Destructor for Game
 */
Game::~Game() {
  delete board;
  delete level;
}

/*
  Constructor for Game, initialize the level as Beginner for the current brute force AI algorithms and initialize the board. Finally set winState to NONE.
 */
Game::Game(int myLevel) {
  Running = true;
  level = new Level("Beginner", 8, 8, 10);
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
  bool initial = true;
  
  while(Running) {
    while(SDL_PollEvent(&Event)) {
      OnEvent(&Event);
    }
    if(winState == NONE) {
      if(initial) {
	board -> OnRender(NONE);
        randomMark();
	render();
	initial = false;
      } else {
	flagBombs();
      }
    }
  }
  return 0;
}

/*
  Method to render the game.
 */
void Game::render() {
  checkWin();
  SDL_Delay(50);
  if(winState == LOSE) {
    board -> OnRender(LOSE);
    reset();
  } else if(winState == WIN) {
    board -> OnRender(WIN);
  } else {
    board -> OnRender(NONE);
  }
}

/*
  Method to reset the game by calling reset in board.
 */
void Game::reset() {
  board -> reset();
}

/*
  Method to check the win state of the game.
 */

// Must marked all the cells that are not bomb
void Game::checkWin() {
  if(board -> getNumBomb() + board -> getNumMarked() == board -> getNumTotal()) {
    winState = WIN;
    board->OnRender(WIN);
  }
}

/*
  Method to count the number of free squares around a grid.
 */
int Game::countFreeSquares(int row, int col) {
  int width = board->getWidth();
  int height = board->getHeight();
  int count = 0;
  for(int i = -1; i < 2; ++i) {
    for(int j = -1; j < 2; ++j) {
      if(col + j >= 0 && col + j < width && row + i >= 0 && row + i < height) {
	if(!board->isGridMarked(row + i, col + j) && !board->isGridFlagged(row + i, col + j)) {
	  count++;
	}
      }
    }
  }
  return count;
}

/*
  Method to count the number of flags around a grid.
 */
int Game::countFlags(int row, int col) {
  int width = board->getWidth();
  int height = board->getHeight();
  int count = 0;
  for(int i = -1; i < 2; ++i) {
    for(int j = -1; j < 2; ++j) {
      if(col + j >= 0 && col + j < width && row + i >= 0 && row + i < height) {
	if(board->isGridFlagged(row + i, col + j)) {
	  count++;
	}
      }
    }
  }
  return count;
}

/*
  Method to flag the bombs by calling setFlag, setGrid or randomMark correspondingly.
 */
void Game::flagBombs() {
  int width = board->getWidth();
  int height = board->getHeight();
  int flagsAround = 0;
  int freeCellAround = 0;
  bool setGrid = false;
  for(int i = 0; i < height; ++i) {
    for(int j = 0; j < width; ++j) {
      if(!board->isGridMarked(i, j) || board->isGridFlagged(i, j) || board->getGridCount(i, j) == 0) {
	continue;
      }
      flagsAround = countFlags(i, j);
      freeCellAround = countFreeSquares(i, j);
      if(board->getGridCount(i, j) == freeCellAround + flagsAround && freeCellAround != 0) {
	//std::cout << "setFlag" << std::endl;
	setFlag(i, j);
	setGrid = true;
	render();
      }
      if(board->getGridCount(i, j) == flagsAround && freeCellAround != 0) {
	//std::cout << "setMark" << std::endl;
	setMark(i, j);
	setGrid = true;
	render();
      }
    }
  }
  if(!setGrid) {
    //std::cout << "randomMark" << std::endl;
    randomMark();
    render();
  }
}

/*
  Method to set the flags
 */
void Game::setFlag(int row, int col) {
  int width = board->getWidth();
  int height = board->getHeight();
  for(int i = -1; i < 2; ++i) {
    for(int j = -1; j < 2; ++j) {
      if(col + j >= 0 && col + j < width && row + i >= 0 && row + i < height) {
	if(!board->isGridMarked(row + i, col + j) && !board->isGridFlagged(row + i, col + j)) {
	  //std::cout << row+i << ", " << col+j << std::endl;
	  board->setFlagState(row + i, col + j, true);
	}
      }
    }
  }
}

/*
  Method to set the marks
 */
void Game::setMark(int row, int col) {
  int width = board->getWidth();
  int height = board->getHeight();
  for(int i = -1; i < 2; ++i) {
    for(int j = -1; j < 2; ++j) {
      if(col + j >= 0 && col + j < width && row + i >= 0 && row + i < height) {
	if(!board->isGridMarked(row + i, col + j) && !board->isGridFlagged(row + i, col + j)) {
	  //std::cout << row+i << ", " << col+j << std::endl;
	  board->setGridMarked(row + i, col + j);
	  if(board->getGridCount(row + i, col + j) == 0) {
	    board->incrementNumMarked();
	    board->setHintRegion(row + i, col + j);
	  } else {
	    board->incrementNumMarked();
	  }
	}
      }
    }
  }
}

/*
  Method to randomly mark within the board
 */
// Further Potential Optimization: random select from the empty spots only!!!
void Game::randomMark() {
  int width = board->getWidth();
  int height = board->getHeight();
  int row = randomGenerator(height);
  int col = randomGenerator(width);
  if(board -> isGridMarked(row, col) || board -> isGridFlagged(row, col)) {
    return;
  }
  board -> setGridMarked(row, col);
  //std::cout << row << ", " << col << std::endl;
  if(board -> isGridBomb(row, col)) {
    board->setBombClicked(row, col);
    winState = LOSE;
  } else {
    int count = board -> getGridCount(row, col);
    if(count == 0) {
      board -> incrementNumMarked();
      board->setHintRegion(row, col);
    } else {
      board -> incrementNumMarked();
    }
  }
}

/*
  Method to generate random numbers
 */
int Game::randomGenerator(int limit) {
  return rand() % limit;
}

/*
  Method to handle SDL events. In this case, when user clicks on the 'x', the program is terminated by setting Running to false.
 */
void Game::OnEvent(SDL_Event* Event) {
  if(Event->type==SDL_QUIT) {
    Running = false;
  }
}

/*
  Method to exit the program
 */
void Game::OnExit() {
  Running = false;
}

/*
  Method declared in game.h but not used here at AI.
 */
void Game::OnRButtonDown(int mX, int mY) {
  return;
}

/*
  Method declared in game.h but not used here at AI.
 */
void Game::OnLButtonDown(int mX, int mY) {
  return;
}
