#include "std_lib_facilities_4.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>

class Tile : public Fl_Button {
	using Fl_Button::Fl_Button;
	bool containsMine = false;
	bool beenClicked = false;
	int numbRightClicks = 0;
	int adjacentMines = 0;
	int xCoordinate;
	int yCoordinate;
	
	public:
		Tile(int, int, int, int);
		void addMine();
		bool hasMine();
		void incrementAdjacentMines();
		int getAdjacentMines();
		void displayClickedTile();
		void setXYCoordinate(int, int);
		int getXCoordinate();
		int getYCoordinate();
		void setBeenClicked();
		bool hasBeenClicked();
		void setRightClicks(int);
		int getRightClicks();
		void displayMine();
		void displayIncorrectMine();
		void displayLosingMine();
};
