// poWindow.h
#ifndef POWINDOW_H
#define POWINDOW_H
#include "../div.h"
#include "homePage.h"

class Div;
class PoWindow : public Div
{
	private:
		void addElements();

	public:
		PoWindow(std::string name, int yPos, int xPos, int height, int width, std::string poNumber);
		PoWindow(std::string name, int height, int width, std::string poNumber);
		void handleInput(int ch);
};

#endif
