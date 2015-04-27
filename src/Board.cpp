#include "imports/std_lib_facilities_4.h"
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include "imports/Board.h"
#ifndef smileyCallback
void smileyCallback(Fl_Widget* widget);
#endif

void timerCallback(void* data) {
	Board* board = (Board*) data;
	board->incrementTimer();
	Fl::repeat_timeout(1.0, timerCallback, data);
}

Board::Board(int w, int h, int m): Fl_Group(0, 0, tileSize*w, tileSize*h + 52, "") {
	this->begin();
	for (int x = 0; x < w; x += 1) {
		for (int y = 0; y < h; y += 1) {
			Tile *tilePtr = new Tile(x*tileSize, y*tileSize + 52, tileSize, tileSize);
			XYCoordinates.push_back(vector<Tile*>());
			XYCoordinates[x].push_back(tilePtr);
		}
	}
	timer = new Fl_Box(0, 8, tileSize*w/3, 42, "0");
	Fl_Box* timerLabel = new Fl_Box(0, 4, tileSize*w/3, 10, "Timer");
	
	smiley = new Fl_Button(tileSize*w/2 - 21, 5, 42, 42);
	smiley->image(normalSmiley->copy(42, 42));
	smiley->callback(smileyCallback);
	
	minesRemaining = new Fl_Box(tileSize*2*w/3, 8, tileSize*w/3, 42, "");
	minesRemaining->copy_label(to_string(m).c_str());
	Fl_Box* minesLabel = new Fl_Box(tileSize*2*w/3, 4, tileSize*w/3, 10, "Mines Left");
	this->end();
	width = w;
	height = h;
	numbMines = m;
	maxClicks = w*h - m;
	generateMines();
}

void Board::generateMines() {
	srand(time(NULL));
	int x, y;
	for (int i = 0; i < numbMines; i++) {
		x = rand() % width;
		y = rand() % height;
		while (XYCoordinates[x][y]->hasMine()) {
			x = rand() % width;
			y = rand() % height;
		}
		XYCoordinates[x][y]->addMine();
		incrementSurroundings(x, y);
	}
}

void Board::incrementSurroundings(int x, int y) {
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (x+i >= 0 && x+i < width && y+j >= 0 && y+j < height) {
				XYCoordinates[x+i][y+j]->incrementAdjacentMines();
			}
		}
	}
}

int Board::showBoard() {
	this->show();
	return Fl::run();
}

int Board::getNumbFlags() {
	return numbFlags;
}

void Board::addNumbFlags(int i) {
	numbFlags += i;
}

int Board::getNumbMines() {
	return numbMines;
}

int Board::getWidth() {
	return width;
}

int Board::getHeight() {
	return height;
}

void Board::addTileClicked() {
	tilesClicked += 1;
}

bool Board::winGame() {
	return tilesClicked == maxClicks;
}

void Board::displayAllMines(bool playerWin) {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			Tile* tile = XYCoordinates[x][y];
			if (tile->hasMine() == false && tile->getRightClicks() == 1) {
				tile->displayIncorrectMine();
			} else if (tile->hasMine() && playerWin) {
				tile->image(flaggedMine->copy(tileSize, tileSize));
			} else if (tile->hasMine() && tile->getRightClicks() != 1 && playerWin == false) {
				tile->displayMine();
			}
			tile->redraw();
			tile->deactivate();
		}
	}
}

void Board::startTimer() {
	Fl::add_timeout(1.0, timerCallback, this);
	timerRunning = true;
}

void Board::stopTimer() {
	Fl::remove_timeout(timerCallback);
	timerRunning = false;
}

void Board::incrementTimer() {
	int temp = atoi(timer->label());
	temp += 1;
	timer->copy_label(to_string(temp).c_str());
	timer->redraw();
}

bool Board::timerIsRunning() {
	return timerRunning;
}

void Board::setGameOver() {
	gameEnded = true;
}

bool Board::gameOver() {
	return gameEnded;
}
