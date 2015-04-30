#include "imports/callbacks.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_JPEG_Image.H>

Tile::Tile(int x, int y, int w, int h):Fl_Button(x, y, w, h) {
	setXYCoordinate(x/w, (y-72)/h); // The -72 is because of the 72 pixels at the top of the board for timer, etc.
	this->image(coveredTile->copy(tileSize,tileSize));
	this->callback(tileCallback);
}

void Tile::addMine() { 
	containsMine = true;
}

bool Tile::hasMine() {
	return containsMine;
}

void Tile::incrementAdjacentMines() {
	adjacentMines += 1;
}

int Tile::getAdjacentMines() {
	return adjacentMines;
}

/**
 * The vector uncoveredTiles contains pointers.
 * The 0th index corresponds to an uncovered tile with 0 adjacent mines.
 * The 1st index corresponds to an uncovered tile with 1 adjacent mines.
 * Etc.
 */
void Tile::displayClickedTile() {
	this->image(uncoveredTiles[adjacentMines]->copy(tileSize,tileSize));
}

void Tile::displayMine() {
	this->image(mine->copy(tileSize,tileSize));
}

void Tile::displayIncorrectMine() {
	this->image(incorrectMine->copy(tileSize,tileSize));
}

void Tile::displayLosingMine() {
	this->image(losingMine->copy(tileSize,tileSize));
}

void Tile::setXYCoordinate(int x, int y) {
	xCoordinate = x;
	yCoordinate = y;
}

int Tile::getXCoordinate() {
	return xCoordinate;
}

int Tile::getYCoordinate() {
	return yCoordinate;
}

void Tile::setBeenClicked() {
	beenClicked = true;
}

bool Tile::hasBeenClicked() {
	return beenClicked;
}

void Tile::setRightClicks(int i) {
	numbRightClicks = i;
}

int Tile::getRightClicks() {
	return numbRightClicks;
}
