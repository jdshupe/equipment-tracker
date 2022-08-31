// homePage.cpp
#include "homePage.h"
extern Div* activeWindow;

HomePage::HomePage(std::string name, int yPos, int xPos, int height, int width)
	: Div(name, yPos, xPos, height, width)
{
	addElements();
}


HomePage::HomePage(std::string name, int height, int width)
	: Div(name, height, width)
{
	addElements();
}


void HomePage::addElements()
{
	// add table to div
	std::string headers = "PO Number,Description,Price,Start Date,End Date ";
	std::string widths = "14,50,10,11,11";
	Table* header_table = new Table("Main", this, LINES-6, COLS-2, 1, 1, headers, widths);
	header_table->query("\
			SELECT \
				o.number as \"PO Number\",\
				e.description as \"Description\",\
				od.unit_cost as \"Price\",\
				o.start_date as \"Start Date\",\
				o.start_date + (o.rental_duration * o.cycle_length) as \"End Date\" \
			FROM purchase_order o \
			JOIN purchase_order_details od on od.purchase_order_id = o.id \
			JOIN equipment e on od.equipment_id = e.id \
				WHERE e.is_equipment");
	header_table->refreshData();

	wrefresh(win());
}

void HomePage::handleInput(int ch)
{
	switch(ch)
	{
		case KEY_DOWN:
		case 'j':
			child("Main")->rowDown();
			break;
		case KEY_UP:
		case 'k':
			child("Main")->rowUp();
			break;
		case 'n':
			NewRental* rentalWindow = new NewRental("New Rental", 20, 60);
			activeWindow = rentalWindow;
	}
}
