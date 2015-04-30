#include "std_lib_facilities_4.h"
#include <FL/Fl_JPEG_Image.H>

/**
 * This contains static pointers to the images used for minesweeper.
 */

static int tileSize = 24;

static Fl_JPEG_Image* normalSmiley = new Fl_JPEG_Image("tileImages/normalSmiley.jpg");
static Fl_JPEG_Image* loseSmiley = new Fl_JPEG_Image("tileImages/loseSmiley.jpg");
static Fl_JPEG_Image* winSmiley = new Fl_JPEG_Image("tileImages/winSmiley.jpg");
static Fl_JPEG_Image* invalidSmiley = new Fl_JPEG_Image("tileImages/invalidSmiley.jpg");

static Fl_JPEG_Image* coveredTile = new Fl_JPEG_Image("tileImages/coveredTile.jpg");
static Fl_JPEG_Image* flaggedMine = new Fl_JPEG_Image("tileImages/flaggedMine.jpg");
static Fl_JPEG_Image* incorrectMine = new Fl_JPEG_Image("tileImages/incorrectMine.jpg");
static Fl_JPEG_Image* losingMine = new Fl_JPEG_Image("tileImages/losingMine.jpg");
static Fl_JPEG_Image* mine = new Fl_JPEG_Image("tileImages/mine.jpg");
static Fl_JPEG_Image* question = new Fl_JPEG_Image("tileImages/question.jpg");

static vector<Fl_JPEG_Image*> uncoveredTiles = {
	new Fl_JPEG_Image("tileImages/emptyUncoveredTile.jpg"),
	new Fl_JPEG_Image("tileImages/1.jpg"),
	new Fl_JPEG_Image("tileImages/2.jpg"),
	new Fl_JPEG_Image("tileImages/3.jpg"),
	new Fl_JPEG_Image("tileImages/4.jpg"),
	new Fl_JPEG_Image("tileImages/5.jpg"),
	new Fl_JPEG_Image("tileImages/6.jpg"),
	new Fl_JPEG_Image("tileImages/7.jpg"),
	new Fl_JPEG_Image("tileImages/8.jpg")
};
