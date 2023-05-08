// newRental.cpp
#include "newRental.h"
extern Div* activeWindow;
extern HomePage* header_win;

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
	//activeWindow = &this;
}


/**
 * This method is called upon creation of the class. It handles adding all the
 * elements to the div. This currently also handles the queries for selections.
 * This process may be moved in the future to minimize the delay when initially
 * drawing.
 */
void NewRental::addElements()
{
	// add text labels to the top section of the form. This is for info about 
	// the rental as a whole
	new Text("PoNumber",	this,	"PO Number:",		1, 2);
	child("PoNumber")->highlight();
	Selection* supplierSel = new Selection("Supplier", "Supplier:", this, 1, 20, 2, 2);

	new Text("Duration",	this,	"Duration:",		3, 2);
	new Text("Length",		this,	"Cycle Length:",	4, 2);
	new Text("StartDate",	this,	"Start Date:",		5, 2);

	// add text labels to the table for line items
	Text textLabelForDescription("Description", this,	"Description",		7, 3,	true);
	Text textLabelForCost		("Cost",		this,	"Cost",				7, 35,	true);

	Selection* descriptionSel = new Selection("repeat1", "1.", this, 1, 30, 8, 1);
	new Text("repeatCost1", this, " ", descriptionSel->y(), 33, false, 7);

	supplierSel->populateData(database::select("SELECT name FROM supplier;"),1);
	descriptionSel->populateData(database::select(
				"SELECT description, code FROM equipment;"
				), 2);
}


/**
 * adds costing lines to the screen.
 *
 * @param bool repeatable if true the charge added is repeatable and is handled
 * appropriately. 
 */
void NewRental::addLine(bool repeatable)
{
	std::string name, label, numberAsString;
	std::string lastRowName;
	if (repeatable)
	{
		numberAsString = std::to_string(++monthlyFeeRows);
		name = "repeat";
		lastRowName = "repeat" + std::to_string(monthlyFeeRows-1);
	} else {
		numberAsString = std::to_string(++oneTimeFeeRows);
		name = "single";
	}

	new Selection(name + numberAsString, numberAsString + ".", this, 1, 30,
			child(lastRowName)->y()+1, 1);
	child(name + numberAsString)->populateData(database::select( "SELECT description, code FROM equipment;"), 2);
	new Text(name + "Cost" + numberAsString, this, " ",
			child(name + numberAsString)->y(), 33, false, 7);
}


/**
 * called from the main loop to catch key inputs. This currently is set up to
 * handle the following inputs
 *
 * @key F2			add repeatable line
 * @key F3			submit form and send to database
 * @key ENTER		get data for the currently selected input item, calls the
 *					"getData" method for the appropriate element
 * @key (Up/Down Arrows)/(j/k) 
 *					navigate the list of data elements, uses the following 2 methods.
 */
void NewRental::handleInput(int ch)
{
	switch (ch)
	{
		case KEY_F(2):
			addLine(true);
			break;

		case KEY_F(3):
			submit();
			break;

		case 10:
			// remove highlighted label and get data
			m_children[selectedChild]->Draw();
			m_children[selectedChild]->getData();

			nextChild();

			// highlight the next item on the form
			m_children[selectedChild]->highlight(); 
			break;

		case KEY_DOWN:
		case 'j':
			m_children[selectedChild]->Draw();
			nextChild();
			m_children[selectedChild]->highlight();
			break;

		case KEY_UP:
		case 'k':
			m_children[selectedChild]->Draw();
			previousChild();
			m_children[selectedChild]->highlight();
			break;
	}
}


/*
 * these 2 functions handle cycling through the options on the form. Called from
 * the handleInput function on the up and down movements
 */
void NewRental::nextChild()
{
	if (this->selectedChild == (m_children.size() - 1))
	{
		selectedChild = 0;
	} else {
		selectedChild++;
	}
}
void NewRental::previousChild()
{
	if (selectedChild == 0)
	{
		selectedChild = m_children.size() - 1;
	} else {
		selectedChild--;
	}
}


void NewRental::submit()
{
	database::insert(std::string(
			"INSERT INTO purchase_order (\
				number, \
				supplier_id, \
				rental_duration, \
				cycle_length, \
				start_date) \
			VALUES ( \
				'") + child("PoNumber")->value() + "', \
				(SELECT id FROM supplier WHERE name ='" + child("Supplier")->value() + "'),\
				'" + child("Duration")->value() + "',\
				'" + child("Length")->value() + "',\
				'" + child("StartDate")->value() + "');");

	for (Element* el : m_children)
	{
		if (el->name().find("repeatCost") != std::string::npos)
		{
			int rowNumber = el->y() - 7;
			Element* descriptionSelection = child("repeat" + std::to_string(rowNumber));
			database::insert(std::string(
				"INSERT INTO purchase_order_details (\
				purchase_order_id,\
				equipment_id,\
				line_number\
				)\
				VALUES (\
					(SELECT id FROM purchase_order WHERE number = '") + child("PoNumber")->value() + "'),\
					(SELECT id FROM equipment WHERE description = '" + descriptionSelection->value() + "'),\
					'" + std::to_string(rowNumber) + "');");
		}
	}
	destroy_win();
	activeWindow = header_win;
	header_win->child("Main")->refreshData();
	wclear(header_win->win());
	header_win->render();
	header_win->child("Main")->render();
}
