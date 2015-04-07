#include "imports/std_lib_facilities_4.h"
#include <sstream>
#include <FL/Fl_Window.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>

int main() {
	Fl_Window win(16*9, 16*9, "Test");
	win.begin();
		Fl_Button but(10, 150, 70, 30, "Hi");
		Fl_JPEG_Image("tileImages/coveredTile.jpg");
	win.end();
	win.show();
		
}