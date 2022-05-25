// newRental.cpp
#include "newRental.h"

NewRental::NewRental(std::string name, int yPos, int xPos, int height, int width)
	: Div(name, yPos, xPos, height, width)
{
	addElements();
}

void NewRental::addElements()
{
	Text po_number(this, "PO Number:", 1, 2);
	Text supplier(this, "Supplier:", 2, 2);
	Text duration(this, "Duration:", 3, 2);
	Text length(this, "Cycle Length:", 4, 2);
	Text startDate(this, "Start Date:", 5, 2);
}

