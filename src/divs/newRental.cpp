// newRental.cpp
#include "newRental.h"

NewRental::NewRental(std::string name, int yPos, int xPos, int height, int width)
	: Div(name, yPos, xPos, height, width)
{
	addElements();
}

NewRental::NewRental(std::string name, int height, int width)
	: Div(name, height, width)
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

	Text description(this, "Description", 7, 2);
	Text code(this, "Code", 7, 50);
	Text cost(this, "Cost", 7, 65);

	char s_poNumber[80], s_supplier[80], s_duration[10], s_length[10], s_startDate[80];
	char s_description[80], s_code[80], s_cost[80];

	echo();
	curs_set(1);

	mvwgetstr(this->win(), 1, po_number.lastCol() + 2, s_poNumber);
	mvwgetstr(this->win(), 2, supplier.lastCol() + 2, s_supplier);
	mvwgetstr(this->win(), 3, duration.lastCol() + 2, s_duration);
	mvwgetstr(this->win(), 4, length.lastCol() + 2, s_length);
	mvwgetstr(this->win(), 5, startDate.lastCol() + 2, s_startDate);

	std::string sqlNewPO;
	std::string sqlRentalDetail;

	sqlNewPO = std::string(
			"INSERT INTO purchase_order (\
				number,\
				supplier_id,\
				rental_duration,\
				cycle_length)\
			VALUES (\
				'") + s_poNumber + std::string("',\
				(SELECT id FROM supplier WHERE name ='") + s_supplier + std::string("'),")
				+ s_duration + std::string(",")
				+ s_length + std::string(");");

	sqlRentalDetail = std::string(
			"INSERT INTO purchase_order_details(purchase_order_id, equipment_id, line_number, description)"
				"VALUES("
					"(SELECT id FROM purchase_order WHERE number = '") + s_poNumber + std::string("'),"
					"(SELECT id FROM equipment WHERE code = '");

	Selection descriptionSel(this, 1, 20, 8, 2);
	descriptionSel.makeSelection();

	noecho();
	curs_set(0);
	//database::insert(sqlNewPO);
	this->destroy_win();
	clear();
	refresh();
}

