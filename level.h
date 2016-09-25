#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <string>
#include <iostream>

using namespace std;

class Level {
 private:
  string level;
  int width;
  int height;
  int numCell;
  int numBomb;
 public:
  Level(string myLevel, int myWidth, int myHeight, int myMineNum);
  string getLevel();
  int getWidth();
  int getHeight();
  int getNumCell();
  int getNumBomb();
  void setLevel(string myLevel);
  void setWidth(int myWidth);
  void setHeight(int myHeight);
  void setNumBomb(int myNumBomb);
};

#endif
