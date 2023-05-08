// poWindow.cpp
#include "poWindow.h"
extern Div* activeWindow;
extern HomePage* header_win;

PoWindow::PoWindow(std::string name, int yPos, int xPos, int height, int width, std::string poNumber)
	: Div(name, yPos, xPos, height, width)
{
	addElements();
}



PoWindow::PoWindow(std::string name, int height, int width, std::string poNumber)
	: Div(name, height, width)
{
	addElements();
}



void PoWindow::addElements()
{

}



void PoWindow::handleInput(int ch)
{
	switch (ch)
	{
		case 'q':
			destroy_win();
			activeWindow = header_win;
			wclear(header_win->win());
			break;
	}
}
