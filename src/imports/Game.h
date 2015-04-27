#include "std_lib_facilities_4.h"
#ifndef Board
class Board;
#endif

struct Game {
	int newGame();
	Board* currentBoard = nullptr;
	void deleteGame();
};
