#include "imports/Settings.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

int main() {
	Fl_Window* win = new Fl_Window(0, 0, 330, 130, "Minesweeper");
	Settings_Window* settings = new Settings_Window(330, 130, "Minesweeper");
	win->end();
	win->show();
	return (Fl::run());
}
