#include "imports/Board.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "imports/Game.h"

int main() {
	/*Game* game = new Game();
	game->newGame();*/
	Fl_Window* test = new Fl_Window(9*24, 9*24+52);
	test->begin();
	Board* currentBoard = new Board(9, 9, 10);
	test->end();
	test->show();
	return Fl::run();
}
