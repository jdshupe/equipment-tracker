// newRental.h
#ifndef NEWRENTAL_H
#define NEWRENTAL_H
#include "../connection.h"
#include "../div.h"
#include "../elements/selection.h"
#include "../elements/text.h"

class Div;
class NewRental : public Div
{
	private:
		void getData();
		void addElements();

	public:
		NewRental(std::string name, int yPos, int xPos, int height, int width);
		NewRental(std::string name, int height, int width);
};

#endif
