#include "imports/std_lib_facilities_4.h"
#include "imports/Simple_window.h"
#include "imports/Graph.h"
#include "imports/Window.h"
#include "imports/GUI.h"
#include "imports/Point.h"

using namespace Graph_lib;

struct Mine_Tile : Button
{};

struct Minesweeper_Window : Graph_lib::Window
{
	Minesweeper_Window(Point xy, int w, int h, const string& title);
	
	private:
		Button Start_Button;
		Button Exit_Button;
		Text Setting_title;
		Text Diff_set_title;
		Text Diff_text;
		Text Num_tiles;
		Text Num_mines;
		Menu Difficulty;
		Button Diff_Menu;
		int x_tile;									//Number of tile columns
		int y_tile;									//Number of tile rows
		int mines_count;						//Total number of mines
		int i = 0;									//Activates the start button
		
		void hide_menu() {Difficulty.hide(); Diff_Menu.show();}
		
		void menu_pressed() 
		{
			Diff_Menu.hide(); 
			Difficulty.show();
		}
		
		void hard_pressed() 
		{
			if (i!=0)
			{
				detach(Start_Button);
			}
			Diff_text.set_label("Selected Difficulty: Hard");
			Num_tiles.set_label("Number of Tiles: 480"); 
			Num_mines.set_label("Number of Mines: 99");
			attach(Start_Button);
			hide_menu();
			++i;
			x_tile = 30;
			y_tile = 16;
			mines_count = 99;
		}
		void medium_pressed() 
		{		
			if (i!=0)
			{
				detach(Start_Button);
			}
			Diff_text.set_label("Selected Difficulty: Medium");
			Num_tiles.set_label("Number of Tiles: 256"); 
			Num_mines.set_label("Number of Mines: 40");
			attach(Start_Button);
			hide_menu();
			++i;
			x_tile = 16;
			y_tile = 16;
			mines_count = 40;
		}
		void easy_pressed() 
		{
			if (i!=0)
			{
				detach(Start_Button);
			}
			Diff_text.set_label("Selected Difficulty: Easy");
			Num_tiles.set_label("Number of Tiles: 81"); 
			Num_mines.set_label("Number of Mines: 10"); 
			attach(Start_Button);
			hide_menu();
			++i;
			x_tile = 9;
			y_tile = 9;
			mines_count = 10;
		}
		
		void quit();
		void next();
		
};

Minesweeper_Window::Minesweeper_Window(Point xy, int w, int h, const string& title)
	:Window{xy,h,w,title},
	Start_Button{Point{180,340}, 90, 20, "Start Game", [](Address, Address pw) {reference_to<Minesweeper_Window>(pw).next();}},
	Exit_Button{Point{300,340}, 90, 20, "Exit Game", [](Address, Address pw) {reference_to<Minesweeper_Window>(pw).quit();}},
	Difficulty{Point{75,150}, 100, 20, Menu::vertical, "Difficulty"},
	Diff_Menu{Point{75,150}, 100, 20, "Difficulty Menu", [](Address,Address pw) {reference_to<Minesweeper_Window>(pw).menu_pressed();}},
	Diff_set_title{Point{330, 135}, "Game Conditions:"},
	Diff_text{Point{300,155}, "Selected Difficulty: ??"},
	Num_tiles{Point{300,175}, "Number of Tiles: ??"},
	Num_mines{Point{300,195}, "Number of Mines: ??"},
	Setting_title{Point{75,145}, "Set The Difficulty:"}
{
	attach(Exit_Button);
	attach(Diff_set_title);
	attach(Diff_text);
	attach(Num_mines);
	attach(Num_tiles);
	attach(Setting_title);
	Difficulty.attach(new Button{Point{0,0},0,0,"Easy",[](Address,Address pw) {reference_to<Minesweeper_Window>(pw).easy_pressed();}});
	Difficulty.attach(new Button{Point{0,0},0,0,"Medium",[](Address,Address pw) {reference_to<Minesweeper_Window>(pw).medium_pressed();}});
	Difficulty.attach(new Button{Point{0,0},0,0,"Hard",[](Address,Address pw) {reference_to<Minesweeper_Window>(pw).hard_pressed();}});
	attach(Difficulty);
	Difficulty.hide();
	attach(Diff_Menu);
}

void Minesweeper_Window::quit()
{
	hide();
}

void Minesweeper_Window::next()
{
	detach(Diff_text);
	detach(Diff_set_title);
	detach(Num_mines);
	detach(Num_tiles);
	detach(Setting_title);
	detach(Difficulty);
	detach(Diff_Menu);
	detach(Start_Button);
	x_tile;
	y_tile;
	mines_count;
}

int main()
{
	Minesweeper_Window win {Point{100,100}, 400, 600, "Minesweeper"};
	return gui_main();
}
