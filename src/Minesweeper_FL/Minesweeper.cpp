#include "std_lib_facilities_4.h"
#include <sstream>
#include <FL/Fl.H> 
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Output.H>
#include "Board.h"

class Minesweeper_Window : public Fl_Window
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

void Minesweeper_Window::start_cb(Fl_Widget* widget)
{
	Fl_Button* S = (Fl_Button*) widget;
	Minesweeper_Window* settings = (Minesweeper_Window*) S->parent();
	settings->Start_Button->hide();
	settings->D_Setting->hide();
	settings->Easy_Button->hide();
	settings->Med_Button->hide();
	settings->Hard_Button->hide();
	settings->Num_Tiles->hide();
	settings->Num_Mines->hide();
	
	int w, h, m;
	w = settings->x_mines;
	h = settings->y_mines;
	m = settings->mines_count;
	Board* x = new Board(w, h, m);
	x->showBoard();
}

void Minesweeper_Window::exit_cb(Fl_Widget* widget)
{
	Fl_Button* Q = (Fl_Button*) widget;
	Minesweeper_Window* settings = (Minesweeper_Window*) Q->parent();
	settings->hide();
}

void Minesweeper_Window::easy_pressed(Fl_Widget* widget)
{
	Fl_Button* E = (Fl_Button*) widget;
	Minesweeper_Window* settings = (Minesweeper_Window*) E->parent();
	settings->Num_Tiles->label("Size of board: 9 x 9 board");
	settings->Num_Tiles->redraw();
	settings->Num_Mines->label("Number of mines: 10 mines");
	settings->Num_Mines->redraw();
	settings->x_mines = 9;
	settings->y_mines = 9;
	settings->mines_count = 10;
}

void Minesweeper_Window::med_pressed(Fl_Widget* widget)
{
	Fl_Button* M = (Fl_Button*) widget;
	Minesweeper_Window* settings = (Minesweeper_Window*) M->parent();
	settings->Num_Tiles->label("Size of board: 16 x 16 board");
	settings->Num_Tiles->redraw();
	settings->Num_Mines->label("Number of mines: 40 mines");
	settings->Num_Mines->redraw();
	settings->x_mines = 16;
	settings->y_mines = 16;
	settings->mines_count = 40;
}

void Minesweeper_Window::hard_pressed(Fl_Widget* widget)
{
	Fl_Button* H = (Fl_Button*) widget;
	Minesweeper_Window* settings = (Minesweeper_Window*) H->parent();
	settings->Num_Tiles->label("Size of board: 16 x 30 board");
	settings->Num_Tiles->redraw();
	settings->Num_Mines->label("Number of mines: 99 mines");
	settings->Num_Mines->redraw();
	settings->x_mines = 30;
	settings->y_mines = 16;
	settings->mines_count = 99;
}

Minesweeper_Window::Minesweeper_Window(int w, int h, const char* title):Fl_Window(w,h,title) 
{ 
	this->begin();
	
	// The start button and its callback
	Start_Button = new Fl_Button(255, 300, 90, 20, "Start Game");
	Start_Button->callback((Fl_Callback*) start_cb, this);
	
	// The Exit button and its callback
	Exit_Button = new Fl_Button(255, 330, 90, 20, "Exit Game");
	Exit_Button->callback((Fl_Callback*) exit_cb, this);
	
	// Settings Title
	D_Setting = new Fl_Box(160, 165, 100, 20, "Set Difficulty:");
	
	// The Easy Button and its callback
	Easy_Button = new Fl_Button(160, 185, 100, 20, "Easy");
	Easy_Button->callback((Fl_Callback*) easy_pressed, this);
	
	// The Medium Button and its callback
	Med_Button = new Fl_Button(160, 205, 100, 20, "Medium");
	Med_Button->callback((Fl_Callback*) med_pressed, this);
	
	// The Hard Button and its callback
	Hard_Button = new Fl_Button(160, 225, 100, 20, "Hard");
	Hard_Button->callback((Fl_Callback*) hard_pressed, this);
	
	// The displays of the conditions of the difficulty
	Num_Tiles  = new Fl_Box(260, 190, 200, 20, "Size of board: 4 x 4 board");
	Num_Mines = new Fl_Box(260, 220, 200, 20, "Number of Mines: 5 mines");
	
	this->end();
}
	
int main()
{
	Minesweeper_Window* win = new Minesweeper_Window(600, 400, "Minesweeper");
	win->show();
	return (Fl::run());
}