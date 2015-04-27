#include "imports/Game.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "imports/Board.h"

void Game::deleteGame() {
	cout << "Before everything" << endl;
	if (this->currentBoard == nullptr) {
		return;
	}
	cout << "Before for loop" << endl;
	for (int x=0; x<currentBoard->getWidth(); x++) {
		for (int y=0; y<currentBoard->getHeight(); y++) {
			cout << "PRE tile" << endl;
			delete currentBoard->XYCoordinates[x][y];
			cout << "Tile" << endl;
		}
	}
	delete currentBoard;
}

int Game::newGame() {
	Fl_Window* test = new Fl_Window(9*24, 9*24+52);
	test->begin();
	currentBoard = new Board(9, 9, 10);
	test->end();
	return Fl::run();
}
