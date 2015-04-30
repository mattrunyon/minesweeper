#include "imports/Settings.h"
#include "imports/Board.h"
#include <FL/fl_ask.H>
#include <FL/Fl_Window.H>

void Settings_Window::start_cb(Fl_Widget* widget)
{
	Fl_Button* S = (Fl_Button*) widget;
	Settings_Window* settings = (Settings_Window*) S->parent();
	Fl_Window* win = (Fl_Window*) settings->parent();
	
	int w, h, m;
	if (settings->wInput->visible()) {
		w = atoi(settings->wInput->value());
		h = atoi(settings->hInput->value());
		m = atoi(settings->mineInput->value());
		if (w*h <= m) {
			fl_alert("There must be less mines than possible tile spaces!");
			return;
		}
	} else {
		w = settings->x_mines;
		h = settings->y_mines;
		m = settings->mines_count;
	}
	
	bool debugMode = false;
	if (settings->debugButton->value()) {
		debugMode = true;
	}
	
	int choice = 1;
	bool gameAlreadyGoing = Fl::next_window(win) != nullptr;
	if (gameAlreadyGoing) {
		choice = fl_choice("Are you sure you want to reset the game?", "Cancel", "Yes", "No");
	}
	if (choice == 1) {
		if (gameAlreadyGoing) {
			Fl_Window* tempWin = Fl::next_window(win);
			Board* tempBoard = (Board*) tempWin->child(0);
			tempBoard->stopTimer();
		}
		Board* board = new Board(w, h, m, debugMode);
		Fl::delete_widget(Fl::next_window(win));
		Fl::delete_widget(win);
		win = new Fl_Window(win->x(), win->y(), board->w(), board->h());
		win->end();
		win->add(board);
		win->show();
	}
	
}

void Settings_Window::easy_pressed(Fl_Widget* widget)
{
	Fl_Button* E = (Fl_Button*) widget;
	Settings_Window* settings = (Settings_Window*) E->parent();
	settings->Num_Tiles->label("Size of board: 9 x 9 board");
	settings->Num_Mines->label("Number of mines: 10 mines");
	settings->D_Setting->label("Set Difficulty: Easy");
	settings->x_mines = 9;
	settings->y_mines = 9;
	settings->mines_count = 10;
	
	settings->wInput->hide();
	settings->hInput->hide();
	settings->mineInput->hide();
	settings->redraw();
}

void Settings_Window::med_pressed(Fl_Widget* widget)
{
	Fl_Button* M = (Fl_Button*) widget;
	Settings_Window* settings = (Settings_Window*) M->parent();
	settings->Num_Tiles->label("Size of board: 16 x 16 board");
	settings->Num_Mines->label("Number of mines: 40 mines");
	settings->D_Setting->label("Set Difficulty: Medium");
	settings->x_mines = 16;
	settings->y_mines = 16;
	settings->mines_count = 40;
	
	settings->wInput->hide();
	settings->hInput->hide();
	settings->mineInput->hide();
	settings->redraw();
}

void Settings_Window::hard_pressed(Fl_Widget* widget)
{
	Fl_Button* H = (Fl_Button*) widget;
	Settings_Window* settings = (Settings_Window*) H->parent();
	settings->Num_Tiles->label("Size of board: 16 x 30 board");
	settings->Num_Mines->label("Number of mines: 99 mines");
	settings->D_Setting->label("Set Difficulty: Hard");
	settings->x_mines = 30;
	settings->y_mines = 16;
	settings->mines_count = 99;
	
	settings->wInput->hide();
	settings->hInput->hide();
	settings->mineInput->hide();
	settings->redraw();
}

void Settings_Window::custom_pressed(Fl_Widget* widget) {
	Fl_Button* C = (Fl_Button*) widget;
	Settings_Window* settings = (Settings_Window*) C->parent();
	settings->Num_Tiles->label("Size of board: ");
	settings->Num_Mines->label("Number of mines: ");
	settings->D_Setting->label("Set Difficulty: Custom");
	
	settings->wInput->show();
	settings->hInput->show();
	settings->mineInput->show();
	settings->redraw();
}

Settings_Window::Settings_Window(int w, int h, const char* title):Fl_Group(0, 0, w,h,title) 
{ 
	this->begin();
	
	// The start button and its callback
	Start_Button = new Fl_Button(110, 105, 90, 20, "Start Game");
	Start_Button->callback((Fl_Callback*) start_cb, this);
	
	// Settings Title
	D_Setting = new Fl_Box(10, 0, 0, 20, "Set Difficulty: Easy");
	D_Setting->align(FL_ALIGN_RIGHT);
	
	// The Easy Button and its callback
	Easy_Button = new Fl_Button(10, 20, 100, 20, "Easy");
	Easy_Button->callback((Fl_Callback*) easy_pressed, this);
	
	// The Medium Button and its callback
	Med_Button = new Fl_Button(10, 40, 100, 20, "Medium");
	Med_Button->callback((Fl_Callback*) med_pressed, this);
	
	// The Hard Button and its callback
	Hard_Button = new Fl_Button(10, 60, 100, 20, "Hard");
	Hard_Button->callback((Fl_Callback*) hard_pressed, this);
	
	Custom_Button = new Fl_Button(10, 80, 100, 20, "Custom");
	Custom_Button->callback((Fl_Callback*) custom_pressed, this);
	
	// The displays of the conditions of the difficulty
	Num_Tiles = new Fl_Box(110, 25, 0, 20, "Size of board: 9 x 9 board");
	Num_Tiles->align(FL_ALIGN_RIGHT);
	Num_Mines = new Fl_Box(110, 55, 0, 20, "Number of mines: 10 mines");
	Num_Mines->align(FL_ALIGN_RIGHT);
	
	wInput = new Fl_Int_Input(210, 25, 50, 20, "");
	wInput->hide();
	hInput = new Fl_Int_Input(280, 25, 50, 20, "");
	hInput->hide();
	mineInput = new Fl_Int_Input(240, 55, 50, 20, "");
	mineInput->hide();
	
	debugButton = new Fl_Check_Button(200, 0, 90, 20, "Debug Mode");
	
	this->end();
}
