#include "std_lib_facilities_4.h"

class Tile {
	bool hasMine;
	bool beenClicked = false;
	bool beenFlagged = false;
	
	public:
		Tile(bool i);
		
};

Tile::Tile(bool i) {
	hasMine = i;
}
