#include "imports/callbacks.h"
#include "imports/Settings.h"
#include <FL/Fl_JPEG_Image.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Window.H>

/**
 * Iterates through the surrounding tiles (-1 to +1 x and y) and simulates a left click on them.
 */
void propagateClick(Tile* tile, Board* board) {
	if (board->debug) {
		cout << "Uncovering all tiles surrounding tile at (" << tile->getXCoordinate() << ", " << tile->getYCoordinate() << ").\n\n";
	}

	int x = tile->getXCoordinate();
	int y = tile->getYCoordinate();
	int width = board->getWidth();
	int height = board->getHeight();
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (x+i >= 0 && x+i < width && y+j >= 0 && y+j < height) {
				Tile* newTile = board->XYCoordinates[x+i][y+j];
				simulateLeftClick(newTile, board);
			}
		}
	}
}

/**
 * What happens on a left click.
 * If a mine has been clicked already, the function returns.
 * If the mine is flagged (right clicks == 1), the function returns.
 * If the tile has a mine, it calls endGame.
 * If the tile does not have a mine, it displays the proper uncoveredTile image.
 * If the tile has 0 adjacent mines, it also propagates the click around the tile with 0 adjacent mines.
 * If it is a win game scenario, calls endGame.
 */
void simulateLeftClick(Tile* tile, Board* board) {
	if (tile->hasBeenClicked()) {
		return;
	}
	if (tile->getRightClicks() == 1) {
		return;
	}
	if (tile->hasMine()) {
		endGame(tile, board);
	} else {
		tile->displayClickedTile();
		tile->setBeenClicked();
		tile->redraw();
		board->addTileClicked();
	}
	if (tile->getAdjacentMines() == 0) {
		propagateClick(tile, board);
	}
	if (board->winGame()) {
		endGame(tile, board);
	}
}

/**
 * Stops the timer and ends the game.
 * If the player won, displays the sunglasses smiley face and all mines as flags.
 * If the player lost, displays the  displays the dead smiley, the losing mine, incorrect mines, and all other mines.
 */
void endGame(Tile* tile, Board* board) {
	board->stopTimer();
	if (board->debug) {
		cout << "Game is ending.\n";
	}
	if (board->winGame()) {
		if (board->debug) {
			cout << "Player won!\n\n";
		}
		board->smiley->image(winSmiley->copy(42, 42));
		board->smiley->redraw();
		board->minesRemaining->copy_label("0");
		board->displayAllMines(true);
	} else {
		if (board->debug) {
			cout << "Player lost.\n\n";
		}
		board->smiley->image(loseSmiley->copy(42, 42));
		board->smiley->redraw();
		board->displayAllMines(false);
		tile->displayLosingMine();
		tile->setBeenClicked();
		tile->redraw();
	}
	board->setGameOver();
}

/**
 * Resets the game using the current settings.
 * If the smiley is clicked and the game is not over, asks if the user wants to reset the game.
 */
void smileyCallback(Fl_Widget* widget) {
	Board* board = (Board*) widget->parent();
	Fl_Window* window = (Fl_Window*) board->parent();
	switch (Fl::event_button()) {
		case FL_LEFT_MOUSE: {
			if (board->gameOver() || fl_choice("Are you sure you want to reset the game?", "Cancel", "Yes", "No") == 1) {
				board->stopTimer();
				int w = board->getWidth();
				int h = board->getHeight();
				int m = board->getNumbMines();
				Fl::delete_widget(board);
				window->begin();
				Board* currentBoard = new Board(w, h, m, board->debug);
				window->end();
				window->redraw();
			}
			break;
		}
	}
}

/**
 * Opens a new settings window.
 */
void settingsCallback(Fl_Widget* widget) {
	Board* board = (Board*) widget->parent();
	Fl_Window* window = (Fl_Window*) board->parent();
	Fl_Window* win = new Fl_Window(0, 0, 330, 160, "Minesweeper");
	Settings_Window* settings = new Settings_Window(330, 160, "Minesweeper");
	win->end();
	win->show();
}

/**
 * Determines what happens when a tile is right or left clicked.
 */
void tileCallback(Fl_Widget* widget) {
	Tile* tile = (Tile*) widget;
	Board* board = (Board*) tile->parent();
	
	if (board->timerIsRunning() == false) {
		board->startTimer();
	}
	int flags = 0;
	int x = tile->getXCoordinate();
	int y = tile->getYCoordinate();
	int width = board->getWidth();
	int height = board->getHeight();
	String debugStmt = "";
	
	// Counts the adjacent flagged tiles.
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (x+i >= 0 && x+i < width && y+j >= 0 && y+j < height && board->XYCoordinates[x+i][y+j]->getRightClicks() == 1) {
				flags += 1;
			}
		}
	}
	
	if (board->debug) {
		cout << "Tile at coordinate (" << x << ", " << y << ") was clicked.\n";
		if (tile->hasMine()) {
			cout << "Tile contains a mine.\n";
		} else {
			cout << "Tile has " << tile->getAdjacentMines() << " adjacent mines and " << flags << " flagged surrounding tiles.\n";
		}
	}
	
	switch (Fl::event_button()) {
		case FL_LEFT_MOUSE: {
			// If it is a right/left simultaneous click on an already uncovered tile with proper surrounding flags.
			if (tile->hasBeenClicked() && Fl::event_button3() != 0 && tile->getAdjacentMines() == flags) {
				debugStmt = "Tile was validly left/right simultaneous clicked.\n\n";
				propagateClick(tile, board);
			} 
			// If the tile has not been clicked and it is a left click only.
			else if (tile->hasBeenClicked() == false && Fl::event_button3() == 0) {
				debugStmt = "Tile was validly left clicked.\n\n";
				simulateLeftClick(tile, board);
			} else {
				debugStmt = "Tile was invalidly left or left/right simultaneous clicked.\n\n";
			}
			break;
		}
		case FL_RIGHT_MOUSE: {		
			// If it is a right/left simultaneous click on an already uncovered tile with proper surrounding flags.
			if (tile->hasBeenClicked() && Fl::event_button1() != 0 && tile->getAdjacentMines() == flags) {
				debugStmt = "Tile was validly left/right simultaneous clicked.\n\n";
				propagateClick(tile, board);
			}
			// If the tile has been clicked and it is a normal right click.
			else if (Fl::event_button1() != 0 || tile->hasBeenClicked()) {
				debugStmt = "Tile was invalidly right or left/right simultaneous clicked.\n\n";
				break;
			}
			// If the tile is blank and there are still flags that can be placed.
			else if (tile->getRightClicks() == 0 && board->getNumbFlags() < board->getNumbMines()) {
				debugStmt = "Tile was validly right clicked. Changing to flag.\n\n";
				tile->image(flaggedMine->copy(tileSize, tileSize));
				tile->setRightClicks(1);
				board->addNumbFlags(1);
				board->minesRemaining->copy_label(to_string(board->getNumbMines() - board->getNumbFlags()).c_str());
			}
			// If the tile is currently flagged.
			else if (tile->getRightClicks() == 1) {
				debugStmt = "Tile was validly right clicked. Changing to question.\n\n";
				tile->image(question->copy(tileSize, tileSize));
				tile->setRightClicks(2);
				board->addNumbFlags(-1);
				board->minesRemaining->copy_label(to_string(board->getNumbMines() - board->getNumbFlags()).c_str());
			}
			// If the tile is currently a question mark.
			else {
				debugStmt = "Tile was validly right clicked. Changing to normal uncovered.\n\n";
				tile->image(coveredTile->copy(tileSize, tileSize));
				tile->setRightClicks(0);
			}
			break;
		}
	}
	if (board->debug) {
		cout << debugStmt;
	}
}
