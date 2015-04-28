#include "Board.h"
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>

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