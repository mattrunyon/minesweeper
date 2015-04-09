#include "imports/std_lib_facilities_4.h"
#include <sstream>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>

int main() {
	Fl_Window win(100, 100, 16*9, 16*9, "Test");
	win.begin();
	int x = 0;
	int y = 0;
	Fl_JPEG_Image tile("tileImages/coveredTile.jpg");
	for (int x = 0; x < 16*9; x += 16) {
		for (int y = 0; y < 16*9; y += 16) {
			Fl_Button *box = new Fl_Button(x, y, 16, 16);
			//box->image(tile);
		}
	}
	win.end();
	win.show();
	return (Fl::run());
}