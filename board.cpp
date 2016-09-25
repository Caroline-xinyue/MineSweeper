#include "board.h"

using namespace std;

/*
  Destructor for Board. Free all the surfaces and delete the 2D array of Grid objects.
 */
Board::~Board() {
  for(int i = 0; i < height; ++i) {
    delete[] grid[i];
  }
  delete[] grid;
  SDL_FreeSurface(Surf_Grid);
  SDL_FreeSurface(Surf_0);
  SDL_FreeSurface(Surf_1);
  SDL_FreeSurface(Surf_2);
  SDL_FreeSurface(Surf_3);
  SDL_FreeSurface(Surf_4);
  SDL_FreeSurface(Surf_5);
  SDL_FreeSurface(Surf_6);
  SDL_FreeSurface(Surf_7);
  SDL_FreeSurface(Surf_8);
  SDL_FreeSurface(Surf_Bomb);
  SDL_FreeSurface(Surf_BombClicked);
  SDL_FreeSurface(Surf_Flag);
  SDL_FreeSurface(Surf_FlagError);
  SDL_FreeSurface(Surf_Display);
  SDL_FreeSurface(Surf_Win);
  SDL_FreeSurface(Surf_Lose);
  SDL_FreeSurface(Surf_Restart);
  SDL_Quit();
}

/*
  Constructor for Board. Set srand to make sure the random generating function is generating different numbers every time. Initialize all surfaces to NULL and initilize the variables and the 2D array of Grid objects.
 */
Board::Board(Level* level) {
  srand(static_cast<unsigned int>(time(nullptr)));
  Surf_Grid = NULL;
  Surf_0 = NULL;
  Surf_1 = NULL;
  Surf_2 = NULL;
  Surf_3 = NULL;
  Surf_4 = NULL;
  Surf_5 = NULL;
  Surf_6 = NULL;
  Surf_7 = NULL;
  Surf_8 = NULL;
  Surf_Bomb = NULL;
  Surf_BombClicked = NULL;
  Surf_Flag = NULL;
  Surf_FlagError = NULL;
  Surf_Win = NULL;
  Surf_Lose = NULL;
  Surf_Restart = NULL;
  width = level -> getWidth();
  height = level -> getHeight();
  grid = new Grid*[height];
  for(int i = 0; i < height; ++i) {
    grid[i] = new Grid[width];
  }
  numBomb = level -> getNumBomb();
  numTotal = level -> getNumCell();
  numMarked = 0;
}

/*
  Init the surfaces and init the bombs. For the purpose of testing AI algorithm, a testboard is provided given conditional compilation.
 */
bool Board::OnInit() {
  string easyGrid  = "gfx/easyGrid.bmp";
  string count0  = "gfx/count0.bmp";
  string count1  = "gfx/count1.bmp";
  string count2  = "gfx/count2.bmp";
  string count3  = "gfx/count3.bmp";
  string count4  = "gfx/count4.bmp";
  string count5  = "gfx/count5.bmp";
  string count6  = "gfx/count6.bmp";
  string count7  = "gfx/count7.bmp";
  string count8  = "gfx/count8.bmp";
  string bomb  = "gfx/bomb.bmp";
  string bombClicked  = "gfx/bombClicked.bmp";
  string flag  = "gfx/flag.bmp";
  string flagError  = "gfx/flagError.bmp";
  string win = "gfx/win.bmp";
  string lose = "gfx/lose.bmp";
  string restart = "gfx/restart.bmp";

  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return false;
  }

  if((Surf_Display = SDL_SetVideoMode(gridSize*width, gridSize*height + topbarH, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    return false;
  }

  if((Surf_Grid = CSurface::OnLoad(easyGrid.c_str())) == NULL) {
    std::cout << "Error loading image easyGrid" << std::endl;
    return false;
  }
  
  if((Surf_0 = CSurface::OnLoad(count0.c_str())) == NULL) {
    std::cout << "Error loading image 0" << std::endl;
    return false;
  }
  
  if((Surf_1 = CSurface::OnLoad(count1.c_str())) == NULL) {
    std::cout << "Error loading image 1" << std::endl;
    return false;
  }
  
  if((Surf_2 = CSurface::OnLoad(count2.c_str())) == NULL) {
    std::cout << "Error loading image 2" << std::endl;
    return false;
  }

  if((Surf_3 = CSurface::OnLoad(count3.c_str())) == NULL) {
    std::cout << "Error loading image 3" << std::endl;
    return false;
  }

  if((Surf_4 = CSurface::OnLoad(count4.c_str())) == NULL) {
    std::cout << "Error loading image 4" << std::endl;
    return false;
  }

  if((Surf_5 = CSurface::OnLoad(count5.c_str())) == NULL) {
    std::cout << "Error loading image 5" << std::endl;
    return false;
  }
  
  if((Surf_6 = CSurface::OnLoad(count6.c_str())) == NULL) {
    std::cout << "Error loading image 6" << std::endl;
    return false;
  }
  
  if((Surf_7 = CSurface::OnLoad(count7.c_str())) == NULL) {
    std::cout << "Error loading image 7" << std::endl;
    return false;
  }
  
  if((Surf_8 = CSurface::OnLoad(count8.c_str())) == NULL) {
    std::cout << "Error loading image 8" << std::endl;
    return false;
  }

  if((Surf_Bomb = CSurface::OnLoad(bomb.c_str())) == NULL) {
    std::cout << "Error loading image bomb" << std::endl;
    return false;
  }

  if((Surf_BombClicked = CSurface::OnLoad(bombClicked.c_str())) == NULL) {
    std::cout << "Error loading image bombClicked" << std::endl;
    return false;
  }
  
  if((Surf_Flag = CSurface::OnLoad(flag.c_str())) == NULL) {
    std::cout << "Error loading image flag" << std::endl;
    return false;
  }

  if((Surf_FlagError = CSurface::OnLoad(flagError.c_str())) == NULL) {
    std::cout << "Error loading image flagError" << std::endl;
    return false;
  }

  if((Surf_Win = CSurface::OnLoad(win.c_str())) == NULL) {
    std::cout << "Error loading image win" << std::endl;
    return false;
  }

  if((Surf_Lose = CSurface::OnLoad(lose.c_str())) == NULL) {
    std::cout << "Error loading image lose" << std::endl;
    return false;
  }
  
  if((Surf_Restart = CSurface::OnLoad(restart.c_str())) == NULL) {
    std::cout << "Error loading image restart" << std::endl;
    return false;
  }
  
  CSurface::Transparent(Surf_Bomb, 0, 0, 0);
  CSurface::Transparent(Surf_BombClicked, 255, 255, 255);
  CSurface::Transparent(Surf_Flag, 0, 0, 0);
  CSurface::Transparent(Surf_FlagError, 0, 0, 0);
  CSurface::Transparent(Surf_Restart, 255, 255, 255);
  CSurface::Transparent(Surf_Lose, 255, 255, 255);

#ifdef TEST
  std::cout << "testAI is defined" << std::endl;
#if TEST == 1
  setAITestBoard();
#elif TEST == 0
  initBomb();
#endif
#endif
  return true;
}

/*
  Method to set up the AI test board.
 */
void Board::setAITestBoard() {
  grid[0][0].cell = 1;
  grid[0][0].isMarked = true;
  grid[0][1].cell = 1;
  grid[0][1].isMarked = true;
  grid[0][3].cell = 0;
  grid[0][4].cell = 0;
  grid[0][5].cell = 0;
  grid[0][6].cell = 1;
  grid[0][6].isMarked = true;
  grid[0][7].cell = 1;
  grid[0][7].isMarked = true;

  grid[1][0].cell = 1;
  grid[1][0].isMarked = true;
  grid[1][1].isBomb = true;
  grid[1][2].cell = 1;
  grid[1][3].cell = 1;
  grid[1][4].cell = 1;
  grid[1][5].cell = 1;
  grid[1][6].cell = 1;
  grid[1][6].isMarked = true;
  grid[1][7].isBomb = true;
  
  grid[2][0].cell = 1;
  grid[2][1].cell = 1;
  grid[2][2].cell = 1;
  grid[2][3].cell = 1;
  grid[2][3].isMarked = true;
  grid[2][4].isBomb = true;
  grid[2][4].isFlagged = true;
  grid[2][5].cell = 2;
  grid[2][6].cell = 2;
  grid[2][7].cell = 2;

  grid[3][0].cell = 1;
  grid[3][1].cell = 2;
  grid[3][2].cell = 2;
  grid[3][3].cell = 2;
  grid[3][4].cell = 1;
  grid[3][5].cell = 2;
  grid[3][6].isBomb = true;
  grid[3][7].cell = 1;

  grid[4][0].cell = 2;
  grid[4][1].isBomb = true;
  grid[4][2].isBomb = true;
  grid[4][3].cell = 2;
  grid[4][3].isMarked = true;
  grid[4][4].cell = 1;
  grid[4][5].cell = 1;
  grid[4][6].cell = 1;
  grid[4][7].cell = 1;

  grid[5][0].cell = 2;
  grid[5][0].isMarked = true;
  grid[5][1].isBomb = true;
  grid[5][2].cell = 5;
  grid[5][2].isMarked = true;
  grid[5][3].isBomb = true;
  grid[5][4].cell = 1;
  grid[5][4].isMarked = true;
  grid[5][5].cell = 0;
  grid[5][6].cell = 1;
  grid[5][7].cell = 1;

  grid[6][0].cell = 1;
  grid[6][1].cell = 2;
  grid[6][2].isBomb = true;
  grid[6][2].isFlagged = true;
  grid[6][3].cell = 2;
  grid[6][3].isMarked = true;
  grid[6][4].cell = 1;
  grid[6][4].isMarked = true;
  grid[6][5].cell = 0;
  grid[6][6].cell = 1;
  grid[6][6].isMarked = true;
  grid[6][7].isBomb = true;

  grid[7][0].cell = 0;
  grid[7][1].cell = 1;
  grid[7][2].cell = 1;
  grid[7][2].isMarked = true;
  grid[7][3].cell = 1;
  grid[7][3].isMarked = true;
  grid[7][4].cell = 0;
  grid[7][4].isMarked = true;
  grid[7][5].cell = 0;
  grid[7][6].cell = 1;
  grid[7][7].cell = 1;
}

/*
  Randomly initialize the bombs.
 */
void Board::initBomb() {
  int row = 0;
  int col = 0;
  int bombs = 0;
  while(bombs < numBomb) {
    row = randomGenerator(height);
    col = randomGenerator(width);
    if(!grid[row][col].isBomb) {
      grid[row][col].isBomb = true;
      bombs++;
    }
  }
}

/*
  Method to generate random numbers within the limit.
 */
int randomGenerator(int limit) {
  return rand() % limit;
}

/*
  Method to count the number of neighbors around the cell at given row and col.
 */
// Assert: grid[row][col] is not bomb, therefore counting neighbors for 9 cells is the same as counting neighbors for 8 cells
int Board::countNeighbors(int row, int col) {
  int count = 0;
  for(int i = -1; i < 2; ++i) {
    for(int j = -1; j < 2; ++j) {
      if(col + j >= 0 && col + j < width && row + i >= 0 && row + i < height) {
	if(grid[row + i][col + j].isBomb) {
	  count++;
	}
      }
    }
  }
  return count;
}

/*
  Reset the board.
 */
void Board::reset() {
  for(int i = 0; i < height; ++i) {
    for(int j = 0; j < width; ++j) {
      grid[i][j].cell = -1;
      grid[i][j].isBomb = false;
      grid[i][j].isBombClicked = false;
      grid[i][j].isMarked = false;
      grid[i][j].isFlagged = false;
    }
  }
  numMarked = 0;
  initBomb();
}

/*
  Method to render the board based on the given winStates. If the winState is 2, meaning that the user loses, render the board displaying all the correct location of bombs. Else, render the board with hinted counts for the grids clicked by the user.
 */
void Board::OnRender(int winState) {
  renderTopbar(winState);
  renderBoard();
  int X = 0;
  int Y = 0;
  int count = 0;
  for(int i = 0; i < height; ++i) {
    for(int j = 0; j < width; ++j) {
      X = j * gridSize;
      Y = i * gridSize + topbarH;
      count = grid[i][j].cell;
      if(winState == 2) {
	if(grid[i][j].isFlagged && !grid[i][j].isBomb) {
	  CSurface::OnDraw(Surf_Display, Surf_FlagError, X, Y);
	} else if(grid[i][j].isFlagged) {
	  CSurface::OnDraw(Surf_Display, Surf_Flag, X, Y);
	} else if(grid[i][j].isBombClicked) {
	  CSurface::OnDraw(Surf_Display, Surf_BombClicked, X, Y);
	} else if(grid[i][j].isBomb) {
	  CSurface::OnDraw(Surf_Display, Surf_Bomb, X, Y);
	} else if(grid[i][j].isMarked) {
	  OnRenderMarked(X, Y, count);
	}
	grid[i][j].isMarked = true; // freeze the board, so that player cannot mark anymore.
      } else {
	if(grid[i][j].isFlagged) {
	  CSurface::OnDraw(Surf_Display, Surf_Flag, X, Y);
	} else if(grid[i][j].isMarked) {
	  OnRenderMarked(X, Y, count);
	}
      }
    }
  }
  SDL_Flip(Surf_Display);
}

/*
  Render the top bar for display of winnign state. A smily face is shown normally. If the user wins, a cool face is shown, else a sad face is shown. When user click on the face, the board get reset and the game gets restart.
 */
void Board::renderTopbar(int winState) {
  if(winState == 1) {
    CSurface::OnDraw(Surf_Display, Surf_Win, width*gridSize/2 - topbarH/2, 0);
  } else if(winState == 2){
    CSurface::OnDraw(Surf_Display, Surf_Lose, width*gridSize/2 - topbarH/2, 0);
  } else {
    CSurface::OnDraw(Surf_Display, Surf_Restart, width*gridSize/2 - topbarH/2, 0);
  }
}

/*
  Render the background board.
 */
void Board::renderBoard() {
  int X = 0;
  int Y = 0;
  for(int i = 0; i < height; ++i) {
    for(int j = 0; j < width; ++j) {
      X = j * gridSize;
      Y = i * gridSize + topbarH;
      CSurface::OnDraw(Surf_Display, Surf_Grid, X, Y);
    }
  }
}

/*
  Based on the counts of neighboring bombs for a given cell, this method renders the numbered hints for users.
 */
void Board::OnRenderMarked(int X, int Y, int count) {
  switch(count) {
  case 0:
    CSurface::OnDraw(Surf_Display, Surf_0, X, Y);
    break;
  case 1:
    CSurface::OnDraw(Surf_Display, Surf_1, X, Y);
    break;
  case 2:
    CSurface::OnDraw(Surf_Display, Surf_2, X, Y);
    break;
  case 3:
    CSurface::OnDraw(Surf_Display, Surf_3, X, Y);
    break;
  case 4:
    CSurface::OnDraw(Surf_Display, Surf_4, X, Y);
    break;
  case 5:
    CSurface::OnDraw(Surf_Display, Surf_5, X, Y);
    break;
  case 6:
    CSurface::OnDraw(Surf_Display, Surf_6, X, Y);
    break;
  case 7:
    CSurface::OnDraw(Surf_Display, Surf_7, X, Y);
    break;
  case 8:
    CSurface::OnDraw(Surf_Display, Surf_8, X, Y);
    break;
  }
}

// getters and setters
int Board::getWidth() {
  return width;
}

int Board::getHeight() {
  return height;
}

int Board::getGridSize() {
  return gridSize;
}

int Board::getNumBomb() {
  return numBomb;
}

int Board::getNumMarked() {
  return numMarked;
}

int Board::getNumTotal() {
  return numTotal;
}

int Board::getGridCount(int row, int col) {
  // lazy initialization
  if(grid[row][col].isMarked &&
     grid[row][col].cell == -1) {
    grid[row][col].cell = countNeighbors(row, col);
  }
  return grid[row][col].cell;
}

int Board::getTopbarH() {
  return topbarH;
}

bool Board::isGridBomb(int row, int col) {
  if(!grid[row][col].isMarked) {
    return false;
  }
  return grid[row][col].isBomb;
}

bool Board::isGridMarked(int row, int col) {
  return grid[row][col].isMarked;
}

bool Board::isGridFlagged(int row, int col) {
  return grid[row][col].isFlagged;
}

void Board::setFlagState(int row, int col, bool flagState) {
  grid[row][col].isFlagged = flagState;
}

void Board::setGridMarked(int row, int col) {
  grid[row][col].isMarked = true;
}

void Board::setBombClicked(int row, int col) {
  grid[row][col].isBombClicked = true;
}

void Board::incrementNumMarked() {
  numMarked++;
}

/*
  Handle the event the user click the left button. Specifically, for a non-marked and non-flagged cell, set the grid boolean of isBombClicked to be true and return true indicating that the user loses. Else, either when a user click on the empty grid, a whole hint region is being set or the hinted number for the grid that user clicks on is calculated.
 */
bool Board::LButtonClicked(int row, int col) {
  if(grid[row][col].isFlagged || grid[row][col].isMarked) {
    return false;
  }
  grid[row][col].isMarked = true;
  if(grid[row][col].isBomb) {
    grid[row][col].isBombClicked = true;
    return true;
  } else {
    int count = getGridCount(row, col);
    if(count == 0) {
      numMarked++;
      setHintRegion(row, col);
    } else {
      numMarked++;
    }
    return false;
  }
}

/*
  Handle the event that the user clicks on right button. Specifically, for a non-marked grid, if the grid is not flagged, set it to flagged; else set the flag state to false.
 */
void Board::RButtonClicked(int row, int col) {
  if(grid[row][col].isMarked) {
    return;
  }
  if(grid[row][col].isFlagged) {
    grid[row][col].isFlagged = false;
  } else {
    grid[row][col].isFlagged = true;
  }
}

/*
  Using recursion to achieve the result of a breadth first search of all the empty cells until all border cells are non-empty.
 */
// Assert: grid[row][col].cell is 0
void Board::setHintRegion(int row, int col) {
  int count = getGridCount(row, col);
  if(count == -1) {
    std::cout << "This shouldn't happen!" << std::endl;
    return;
  }
  if(count != 0) {
    return;
  }
  for(int i = -1; i < 2; ++i) {
    for(int j = -1; j < 2; ++j) {
      if(col + j >= 0 && col + j < width && row + i >= 0 && row + i < height) {
	if(grid[row + i][col + j].isMarked) {
	  continue;
	}
	grid[row + i][col + j].isMarked = true;
	//std::cout << row+i << ", " << col+j << std::endl;
	numMarked++;
	setHintRegion(row + i, col + j);
      }
    }
  }
}
