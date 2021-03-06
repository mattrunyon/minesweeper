#include "std_lib_facilities_4.h"
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include "Board.h"

void tileCallback(Fl_Widget*);
void propagateClick(Tile*, Board*);
void simulateLeftClick(Tile*, Board*);
void endGame(Tile*, Board*);
void timerCallback(Fl_Widget*);
void smileyCallback(Fl_Widget*);
