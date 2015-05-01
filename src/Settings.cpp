#include "imports/Settings.h"
#include "imports/Board.h"
#include <FL/fl_ask.H>
#include <FL/Fl_Window.H>

void Settings_Window::start_cb(Fl_Widget* widget)
{
	Fl_Button* S = (Fl_Button*) widget;
	Settings_Window* settings = (Settings_Window*) S->parent();
	Fl_Window* win = (Fl_Window*) settings->parent();
	
	bool debugMode = false;
	if (settings->debugButton->value()) {
		debugMode = true;
	}
	
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
	
	int choice = 1;
	bool gameAlreadyGoing = false;
	// Checks to see if a Game window already exists.
	while (Fl::next_window(win) != nullptr && !gameAlreadyGoing) {
		gameAlreadyGoing = Fl::next_window(win)->label() == "Game";
		win = Fl::next_window(win);
	}
	win = (Fl_Window*) settings->parent();
	
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
		win = new Fl_Window(win->x(), win->y(), board->w(), board->h(), "Game");
		win->end();
		win->add(board);
		win->show();
		
		if (debugMode) {
			cout << w << " tiles wide.\n";
			cout << h << " tiles tall.\n";
			cout << m << " mines on the board.\n\n";
		}
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

void Settings_Window::about_pressed(Fl_Widget* widget) {
	Fl_Button* A = (Fl_Button*) widget;
	Settings_Window* settings = (Settings_Window*) A->parent();
	Fl_Window* win = (Fl_Window*) settings->parent();
	bool aboutOpen = false;
	// While a next window exists and an about window has not been found as open.
	while (Fl::next_window(win) != nullptr && !aboutOpen) {
		aboutOpen = Fl::next_window(win)->label() == "About Game";
		win = Fl::next_window(win);
	}
	win = (Fl_Window*) settings->parent();
	
	if (!aboutOpen) {
		settings->aboutWin = new Fl_Window(win->x(), win->y(), 340, 160, "About Game");
		Fl_Box* classInfo = new Fl_Box(0, 0, 340, 20, "TAMU CSCE 121-510 Spring 2015 Final Project");
		Fl_Box* mattBox = new Fl_Box(10, 30, 100, 100);
		Fl_JPEG_Image* matt = new Fl_JPEG_Image("tileImages/MatthewRunyon.jpg");
		mattBox->image(matt->copy(100, 100));
		
		Fl_Box* jamesBox = new Fl_Box(120, 30, 100, 100);
		Fl_JPEG_Image* james = new Fl_JPEG_Image("tileImages/JamesCoy.jpg");
		jamesBox->image(james->copy(100, 100));
		
		Fl_Box* xavierBox = new Fl_Box(230, 30, 100, 100);
		Fl_JPEG_Image* xavier = new Fl_JPEG_Image("tileImages/XavierOsta.jpg");
		xavierBox->image(xavier->copy(100, 100));
		
		Fl_Box* names = new Fl_Box(-8, 140, 340, 20, "Matthew Runyon     James Coy         Xavier Osta");
		
		settings->aboutWin->end();
		settings->aboutWin->show();
	}
}

Settings_Window::Settings_Window(int w, int h, const char* title):Fl_Group(0, 0, w,h,title) 
{ 
	this->begin();
	
	// The start button and its callback
	Start_Button = new Fl_Button(110, 105, 90, 20, "Start Game");
	Start_Button->callback((Fl_Callback*) start_cb, this);
	
	// The about button
	About_Button = new Fl_Button(230, 105, 90, 20, "About Game");
	About_Button->callback((Fl_Callback*) about_pressed, this);
	
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
