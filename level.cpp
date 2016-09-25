#include "level.h"

/* 
   Constructor for Level
*/
Level::Level(string myLevel, int myWidth, int myHeight, int myNumBomb) {
  level = myLevel;
  width = myWidth;
  height = myHeight;
  numCell = width * height;
  numBomb = myNumBomb;
}


// getters and setters
string Level::getLevel() {
  return level;
}

int Level::getWidth() {
  return width;
}

int Level::getHeight() {
  return height;
}

int Level::getNumCell() {
  return numCell;
}

int Level::getNumBomb() {
  return numBomb;
}

void Level::setLevel(string myLevel) {
  level = myLevel;
}

void Level::setWidth(int myWidth) {
  width = myWidth;
}

void Level::setHeight(int myHeight) {
  height = myHeight;
}

void Level::setNumBomb(int myNumBomb) {
  numBomb = myNumBomb;
}
