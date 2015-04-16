#include "std_lib_facilities_4.h"

class Board {
	Fl_Window* board;
	public:
		Board(int w, int h, int m);
		int showBoard();
};

Board::Board(int w, int h, int m) {
	board = new Fl_Window(16*w, 16*h, "Test");
	board->begin();
	for (int x = 0; x < 16*w; x += 16) {
		for (int y = 0; y < 16*h; y += 16) {
			Fl_Button *box = new Fl_Button(x, y, 16, 16);
		}
	}
	board->end();
}

int Board::showBoard() {
	board->show();
	return Fl::run();
}
