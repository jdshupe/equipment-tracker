// newRental.cpp
#include "newRental.h"

/**
 * Class constructor, displays the window with a given width/height a position
 *
 * @param name the name to be displayed in the border
 * @param yPos/xPos the coordinates of the top left corner
 * @param height/width the rows/columns of the box
 */
NewRental::NewRental(std::string name, int yPos, int xPos, int height, int width)
	: Div(name, yPos, xPos, height, width)
{
	addElements();
}


/**
 * Class constructor, same as above except this will center the window on the
 * screen. No coordinates are needed.
 */
NewRental::NewRental(std::string name, int height, int width)
	: Div(name, height, width)
{
	addElements();
}

void NewRental::addElements()
{
	// add text labels to the top section of the form. This is for info about 
	// the rental as a whole
	Text textLabelForPoNumber	("PoNumber",	this, "PO Number:",		1, 2);
	Text textLabelForSupplier   ("Supplier",	this, "Supplier:",		2, 2, true);
	Text textLabelForDuration   ("Duration",	this, "Duration:",		3, 2);
	Text textLabelForLength     ("Length",		this, "Cycle Length:",	4, 2);
	Text textLabelForStartDate  ("StartDate",	this, "Start Date:",	5, 2);

	// add text labels to the table for line items
	Text textLabelForDescription("Description", this, "Description",	7, 2,	true);
	Text textLabelForCode		("Code",		this, "Code",			7, 50,	true);
	Text textLabelForCost		("Cost",		this, "Cost",			7, 65,	true);

	Selection supplierSel("SupplierSelection", this, 1, 20, 2, textLabelForSupplier.lastCol() + 2);
	supplierSel.populateData(database::select("SELECT name FROM supplier;"),1);

	Selection descriptionSel("DescriptionSelection", this, 1, 30, 8, 2);
	descriptionSel.populateData(database::select(
				"SELECT description, code FROM equipment;"
				), 2);

	echo();
	curs_set(1);

	// this section is the input navigation of the form, this will be replaced
	// with transversing an index of element positions
	std::string poNumber = textLabelForPoNumber.getData();
	supplierSel.makeSelection();
	textLabelForLength.Draw();
	std::string duration = textLabelForDuration.getData();
	std::string length = textLabelForLength.getData();
	std::string startDate = textLabelForStartDate.getData();

	std::string sqlNewPO;
	std::string sqlRentalDetail;

	/*sqlNewPO = std::string(
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
			"INSERT INTO purchase_order_details("
				"purchase_order_id,"
				"equipment_id,"
				"line_number,"
				"description)"
			"VALUES("
				"(SELECT id FROM purchase_order WHERE number = '") + s_poNumber + std::string("'),"
					"(SELECT id FROM equipment WHERE code = '");*/

	descriptionSel.makeSelection();

	noecho();
	curs_set(0);
	//database::insert(sqlNewPO);
	this->destroy_win();
	clear();
	refresh();
}

