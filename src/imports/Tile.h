#include "std_lib_facilities_4.h"
#include <FL/Fl_Button.H>

class Tile : Fl_Button {
	bool containsMine = false;
	bool beenClicked = false;
	int numbRightClicks = 0;
	int adjacentMines = 0;
	
	
	public:
		void setMine(bool);
		bool hasMine();
		void incrementAdjacentMines();
		
};

void Tile::setMine(bool i) { 
	this->containsMine = i;
}

bool Tile::hasMine() {
	return this->containsMine;
}

void Tile::incrementAdjacentMines() {
	this->adjacentMines += 1;
}

