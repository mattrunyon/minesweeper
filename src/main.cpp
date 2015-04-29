#include "imports/Minesweeper.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

int main() {
	Fl_Window* win = new Fl_Window(0, 0, 330, 160, "Minesweeper");
	Minesweeper_Window* settings = new Minesweeper_Window(330, 160, "Minesweeper");
	win->end();
	win->show();
	return (Fl::run());
	/*Fl_Window* test = new Fl_Window(9*24, 9*24+52);
	test->begin();
	Board* currentBoard = new Board(9, 9, 10);
	test->end();
	test->show();
	return Fl::run();*/
}
