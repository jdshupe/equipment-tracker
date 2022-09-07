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

		int selectedChild = 0;
		int oneTimeFeeRows = 0;
		int monthlyFeeRows = 1;

	public:
		NewRental(std::string name, int yPos, int xPos, int height, int width);
		NewRental(std::string name, int height, int width);

		void handleInput(int ch);

		void addLine(bool repeatable = false);

		void nextChild();
		void previousChild();
};

#endif
