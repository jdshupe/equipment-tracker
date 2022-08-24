// homePage.h
#ifndef HOMEPAGE_H
#define HOMEPAGE_H
#include "../div.h"
#include "../elements/table.h"
#include "newRental.h"

class Div;
class HomePage : public Div
{
	private:
		void addElements();

	public:
		HomePage(std::string name, int yPos, int xPos, int height, int width);
		HomePage(std::string name, int height, int width);
		void handleInput(int ch);

};

#endif
