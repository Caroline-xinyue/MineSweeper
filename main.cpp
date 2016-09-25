#include "main.h"

/*
  Main method to initialize the game and execute the game.
 */
int main() {
  int myLevel = getInput();
  Game* game = new Game(myLevel);
  game -> OnExecute();
  delete game;
  return 0;
}

/*
  Method to get user input, specifically user's selection of game level.
 */
int getInput() {
  cout << "Please input your selected level -- 0 for Beginner, 1 for Intermediate or 2 for Expert" << endl;
  int level = 0;
  cin >> level;
  while(level != 0 && level != 1 && level != 2) {
    cout << "Please reinput your selected level -- 0 for Beginner, 1 for Intermediate or 2 for Expert" << endl;
    cin >> level;
  }
  switch(level) {
  case 0:
    cout << "Setting up board for Beginner level" << endl;
    break;
  case 1:
    cout << "Setting up board for Intermediate level" << endl;
    break;
  case 2:
    cout << "Setting up board for Expert level" << endl;
    break;
  }
  return level;
}
