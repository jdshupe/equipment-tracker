// newRental.h
#ifndef NEWRENTAL_H
#define NEWRENTAL_H
#include "../div.h"
#include "../text.h"

class Div;
class NewRental : public Div
{
	private:
		void addElements();

	public:
		NewRental(std::string name, int yPos, int xPos, int height, int width);
};

#endif
