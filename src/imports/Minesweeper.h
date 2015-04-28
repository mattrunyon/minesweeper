#include "std_lib_facilities_4.h"
#include <sstream>
#include <FL/Fl.H> 
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Output.H>

class Minesweeper_Window : public Fl_Group
{
	public:
		Minesweeper_Window(int w, int h, const char* title);
		~Minesweeper_Window() {};
		Fl_Button* Start_Button;
		Fl_Button* Exit_Button;
		Fl_Box* D_Setting;
		Fl_Button* Easy_Button;
		Fl_Button* Med_Button;
		Fl_Button* Hard_Button;
		Fl_Box* Num_Tiles;
		Fl_Box* Num_Mines;

	private:
		int x_mines = 4;
		int y_mines = 4;
		int mines_count = 5;
		
		static void start_cb(Fl_Widget* widget);
		static void exit_cb(Fl_Widget* widget);
		static void easy_pressed(Fl_Widget* widget);
		static void med_pressed(Fl_Widget* widget);
		static void hard_pressed(Fl_Widget* widget);
};