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
	// add text labels to the top section of the form. This is for info about the rental as a whole
	Text textLabelForPoNumber(this, "PO Number:", 1, 2);
	Text textLabelForSupplier(this, "Supplier:", 2, 2);
	Text textLabelForDuration(this, "Duration:", 3, 2);
	Text textLabelForLength(this, "Cycle Length:", 4, 2);
	Text textLabelForStartDate(this, "Start Date:", 5, 2);

	// add text labels to the table for line items
	Text textLabelForDescription(this, "Description", 7, 2);
	Text textLabelForCode(this, "Code", 7, 50);
	Text textLabelForCost(this, "Cost", 7, 65);

	Selection supplierSel(this, 1, 30, 2, textLabelForSupplier.lastCol() + 2);
	supplierSel.populateData(database::select("SELECT name FROM supplier;"),1);
	Selection descriptionSel(this, 1, 20, 8, 2);
	descriptionSel.populateData(database::select("SELECT description, code FROM equipment;"), 2);

	char s_poNumber[80], s_supplier[80], s_duration[10], s_length[10], s_startDate[80];
	char s_description[80], s_code[80], s_cost[80];

	echo();
	curs_set(1);

	mvwgetstr(this->win(), 1, textLabelForPoNumber.lastCol() + 2, s_poNumber);
	supplierSel.makeSelection();
	mvwgetstr(this->win(), 3, textLabelForDuration.lastCol() + 2, s_duration);
	mvwgetstr(this->win(), 4, textLabelForLength.lastCol() + 2, s_length);
	mvwgetstr(this->win(), 5, textLabelForStartDate.lastCol() + 2, s_startDate);

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

	descriptionSel.makeSelection();

	noecho();
	curs_set(0);
	//database::insert(sqlNewPO);
	this->destroy_win();
	clear();
	refresh();
}

