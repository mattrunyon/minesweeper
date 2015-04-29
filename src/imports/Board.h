#include "std_lib_facilities_4.h"
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include "TileImages.h"
#include "Tile.h"
#include <FL/Fl_Box.H>
#ifndef Game
struct Game;
#endif

class Board: public Fl_Group {
	void generateMines();
	void incrementSurroundings(int, int);
	int numbMines = 0;
	int width;
	int height;
	int numbFlags = 0;
	int tilesClicked = 0;
	int maxClicks = 0;
	bool timerRunning = false;
	bool gameEnded = false;
	public:
		vector<vector<Tile*>> XYCoordinates;
		Board(int, int, int, bool);
		int showBoard();
		int getNumbFlags();
		void addNumbFlags(int);
		int getNumbMines();
		int getWidth();
		int getHeight();
		void addTileClicked();
		bool winGame();
		void displayAllMines(bool);
		void startTimer();
		void stopTimer();
		bool timerIsRunning();
		void incrementTimer();
		Fl_Box* timer;
		Fl_Button* smiley;
		Fl_Box* minesRemaining;
		Game* currentGame;
		int timerCount = 0;
		void setGameOver();
		bool gameOver();
		bool debug = false;
		Fl_Button* settingsButton;
		Fl_Button* resetButton;
};
