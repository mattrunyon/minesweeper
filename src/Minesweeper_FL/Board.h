#include "std_lib_facilities_4.h"
#include <FL/Fl_Window.H>
#include "TileImages.h"
#include "Tile.h"

class Board : Fl_Window {
	void generateMines();
	void incrementSurroundings(int, int);
	int numbMines = 0;
	int width;
	int height;
	int numbFlags = 0;
	public:
		vector<vector<Tile*>> XYCoordinates;
		Board(int, int, int);
		int showBoard();
		int getNumbFlags();
		void addNumbFlags(int);
		int getNumbMines();
		int getWidth();
		int getHeight();
};
