#include "std_lib_facilities_4.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "TileImages.h"
#include "Tile.h"
#include <FL/Fl_Box.H>

class Board: public Fl_Window {
	void generateMines();
	void incrementSurroundings(int, int);
	int numbMines = 0;
	int width;
	int height;
	int numbFlags = 0;
	int tilesClicked = 0;
	int maxClicks = 0;
	bool timerRunning = false;
	public:
		vector<vector<Tile*>> XYCoordinates;
		Board(int, int, int);
		int showBoard();
		int getNumbFlags();
		void addNumbFlags(int);
		int getNumbMines();
		int getWidth();
		int getHeight();
		void addTileClicked();
		bool winGame();
		void displayAllMines();
		void startTimer();
		void stopTimer();
		bool timerIsRunning();
		void incrementTimer();
		Fl_Box* timer;
		int timerCount = 0;
};
