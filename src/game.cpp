#include "imports/std_lib_facilities_4.h"
#include <sstream>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>
#include "imports/Board.h"

int main() {
	Board* x = new Board(9, 9, 10);
	x->showBoard();
}
