all: game AI

game: main.cpp game.cpp board.cpp level.cpp OnEvent.cpp CSurface.cpp CEvent.cpp
	c++ -g -std=c++11 -DTEST=0 -Wall -l SDL -l SDLmain main.cpp game.cpp board.cpp level.cpp OnEvent.cpp CSurface.cpp CEvent.cpp -o minesweeper

AI: main.cpp AI.cpp board.cpp level.cpp CSurface.cpp CEvent.cpp
	c++ -g -std=c++11 -DTEST=1 -Wall -l SDL -l SDLmain main.cpp AI.cpp board.cpp level.cpp CSurface.cpp CEvent.cpp -o AIminesweeper

clean:
	rm minesweeper
