#include "std_lib_facilities_4.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "Board.h"

Board::Board(int w, int h, int m): Fl_Window(tileSize*w, tileSize*h) {
	this->begin();
	for (int x = 0; x < w; x += 1) {
		for (int y = 0; y < h; y += 1) {
			Tile *tilePtr = new Tile(x*tileSize, y*tileSize, tileSize, tileSize);
			XYCoordinates.push_back(vector<Tile*>());
			XYCoordinates[x].push_back(tilePtr);
		}
	}
	this->end();
	width = w;
	height = h;
	numbMines = m;
	generateMines();
}

void Board::generateMines() {
	srand(time(NULL));
	int x, y;
	cout << numbMines << endl;
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
