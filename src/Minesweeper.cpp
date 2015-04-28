#include "imports/Minesweeper.h"
#include "imports/Board.h"
#include <FL/Fl_Window.H>

void Minesweeper_Window::start_cb(Fl_Widget* widget)
{
	Fl_Button* S = (Fl_Button*) widget;
	Minesweeper_Window* settings = (Minesweeper_Window*) S->parent();
	Fl_Window* win = (Fl_Window*) settings->parent();
	/*settings->Start_Button->hide();
	settings->D_Setting->hide();
	settings->Easy_Button->hide();
	settings->Med_Button->hide();
	settings->Hard_Button->hide();
	settings->Num_Tiles->hide();
	settings->Num_Mines->hide();*/
	win->clear();
	
	int w, h, m;
	w = settings->x_mines;
	h = settings->y_mines;
	m = settings->mines_count;
	Board* board = new Board(w, h, m);
	win->resize(win->x(), win->y(), board->w(), board->h());
	win->add(board);
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

Minesweeper_Window::Minesweeper_Window(int w, int h, const char* title):Fl_Group(0, 0, w,h,title) 
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
	
/*int main()
{
	Minesweeper_Window* win = new Minesweeper_Window(600, 400, "Minesweeper");
	win->show();
	return (Fl::run());
}*/