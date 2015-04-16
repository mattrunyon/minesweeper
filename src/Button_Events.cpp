#include "std_lib_facilities_4.h"
#include "Simple_window.h"
#include "Graph.h"
#include "Window.h"
#include "GUI.h"
#include "Point.h"
#include <FL/Fl_JPEG_Image.H>

using namespace Graph_lib;

//Inherit from button class and create public member functions that changes the display of the button.
struct Changing_Button : Button
{
	Changing_Button(Point xy, int w, int h, const string& label, Callback cb);
	
	//Change the button's background color
	void change_bg_color(Fl_Color c)
	{
		pw->color(c);
	}
	
	//Change the button's image display
	void change_image(Fl_Image* i)
	{
		pw->image(i);
	}
};

Changing_Button::Changing_Button(Point xy, int w, int h, const string& label, Callback cb) : Button{xy,w,h,label,cb} {}

struct Event_Window : Graph_lib::Window
{
	Event_Window(Point xy, int w, int h, const string& title);
	
	private:                                                          
		Changing_Button button_1;
		Changing_Button button_2;
		Button quit_button;
		Fl_JPEG_Image* flag = new Fl_JPEG_Image("flaggedMine.jpg");
		Fl_JPEG_Image* mine = new Fl_JPEG_Image("losingMine.jpg");

		void button_1_pressed()
		{
			switch(Fl::event_button())
			{
				case 1:
				{
					button_1.change_bg_color(FL_BLUE);
					break;
				}
				case 2:
				{
					Fl_JPEG_Image* flag;
					button_1.change_bg_color(FL_BACKGROUND_COLOR);
					button_1.change_image(flag);
					break;
				}
				case 3:
				{
					button_1.change_image(flag);
					break;
				}
			}
		}
		
		void button_2_pressed()
		{
			switch(Fl::event_button())
			{
				case 1:
				{
					button_2.change_bg_color(FL_GREEN);
					break;
				}
				case 2:
				{
					Fl_JPEG_Image* mine;
					button_2.change_bg_color(FL_BACKGROUND_COLOR);
					button_2.change_image(mine);
					break;
				}
				case 3:
				{
					button_2.change_image(mine);
					break;
				}
			}
		}
		
		void quit()
		{
			hide();
		}
};

Event_Window::Event_Window(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title},
	button_1{Point{50,50}, 50, 50, "", [](Address, Address pw) {reference_to<Event_Window>(pw).button_1_pressed();}},
	button_2{Point{200,50}, 50, 50, "", [](Address, Address pw) {reference_to<Event_Window>(pw).button_2_pressed();}},
	quit_button{Point{100,120}, 100, 20, "Exit", [](Address, Address pw) {reference_to<Event_Window>(pw).quit();}}
{
	attach(button_1);
	attach(button_2);
	attach(quit_button);
}

int main()
{
	Event_Window win{Point{100,100}, 300, 150, "Event Buttons Test"};
	return gui_main();
}