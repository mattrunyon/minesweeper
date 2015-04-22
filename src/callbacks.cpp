#include "imports/callbacks.h"
#include <FL/Fl_JPEG_Image.H>

void propagateClick(Tile* tile, Board* board) {
	int test = 0;
	int x = tile->getXCoordinate();
	int y = tile->getYCoordinate();
	int width = board->getWidth();
	int height = board->getHeight();
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (x+i >= 0 && x+i < width && y+j >= 0 && y+j < height) {
				Tile* newTile = board->XYCoordinates[x+i][y+j];
				cout << newTile->getXCoordinate() << endl;
				simulateLeftClick(newTile, board);
			}
		}
	}
}

void simulateLeftClick(Tile* tile, Board* board) {
	cout << tile->getXCoordinate() << endl;
	if (tile->hasBeenClicked()) {
		return;
	}
	if (tile->getRightClicks() == 1) {
		return;
	}
	if (tile->hasMine()) {
		// END GAME
		cout << "LOSER" << endl;
	} else {
		tile->displayClickedTile();
		tile->setBeenClicked();
		tile->redraw();
	}
	//cout << tile->getAdjacentMines() << endl;
	if (tile->getAdjacentMines() == 0) {
		propagateClick(tile, board);
	}
}

void tileCallback(Fl_Widget* widget) {
	Tile* tile = (Tile*) widget;
	Board* board = (Board*) tile->parent();
	if (tile->hasBeenClicked()) {
		return;
	}
	switch (Fl::event_button()) {
		case FL_LEFT_MOUSE: {
			simulateLeftClick(tile, board);
			break;
		}
		case FL_RIGHT_MOUSE: {
			if (tile->getRightClicks() == 0 && board->getNumbFlags() < board->getNumbMines()) {
				tile->image(flaggedMine->copy(tileSize, tileSize));
				tile->setRightClicks(1);
				board->addNumbFlags(1);
			} else if (tile->getRightClicks() == 1) {
				tile->image(question->copy(tileSize, tileSize));
				tile->setRightClicks(2);
				board->addNumbFlags(-1);
			} else {
				tile->image(coveredTile->copy(tileSize, tileSize));
				tile->setRightClicks(0);
			}
			break;
		}
	}
}
