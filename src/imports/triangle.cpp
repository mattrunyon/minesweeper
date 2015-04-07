#include "std_lib_facilities_4.h"
#include "Simple_window.h"
#include "Graph.h"
#include "Window.h"
#include "GUI.h"
#include "Point.h"

int main() {

	Point t1(100,200);
	
	Simple_window win(t1, 600, 400, "Canvas");
	
	Polygon poly;
	
	poly.add(Point(300,200));
	poly.add(Point(350,100));
	poly.add(Point(400,200));
	poly.set_color(Color::red);
	win.attach(poly);
	
	win.wait_for_button();

	return 0;
}