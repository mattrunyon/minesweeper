#include "std_lib_facilities_4.h"
#include <sstream>
#include <FL/Fl.H> 
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Check_Button.H>

class Settings_Window : public Fl_Group
{
	int x_mines = 9;
	int y_mines = 9;
	int mines_count = 10;
	
	static void start_cb(Fl_Widget* widget);
	static void easy_pressed(Fl_Widget* widget);
	static void med_pressed(Fl_Widget* widget);
	static void hard_pressed(Fl_Widget* widget);
	static void custom_pressed(Fl_Widget* widget);
	static void about_pressed(Fl_Widget* widget);
	
	public:
		Settings_Window(int w, int h, const char* title);
		~Settings_Window() {};
		Fl_Button* Start_Button;
		Fl_Box* D_Setting;
		Fl_Button* Easy_Button;
		Fl_Button* Med_Button;
		Fl_Button* Hard_Button;
		Fl_Button* Custom_Button;
		Fl_Box* Num_Tiles;
		Fl_Box* Num_Mines;
		Fl_Int_Input* wInput;
		Fl_Int_Input* hInput;
		Fl_Int_Input* mineInput;
		Fl_Check_Button* debugButton;
		Fl_Button* About_Button;
		Fl_Window* aboutWin = nullptr;
};
