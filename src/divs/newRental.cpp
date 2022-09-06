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
	//activeWindow = &this;
}


void NewRental::addElements()
{
	// add text labels to the top section of the form. This is for info about 
	// the rental as a whole
	Text* textLabelForPoNumber	= new Text("PoNumber",	this,	"PO Number:",		1, 2);
	textLabelForPoNumber->highlight();
	Selection* supplierSel = new Selection("Supplier", this, 1, 20, 2, 2);

	Text* textLabelForDuration	= new Text("Duration",	this,	"Duration:",		3, 2);
	Text* textLabelForLength	= new Text("Length",	this,	"Cycle Length:",	4, 2);
	Text* textLabelForStartDate = new Text("StartDate",	this,	"Start Date:",		5, 2);

	// add text labels to the table for line items
	Text textLabelForDescription("Description", this,	"Description",		7, 3,	true);
	Text textLabelForCode		("Code",		this,	"Code",				7, 30,	true);
	Text textLabelForCost		("Cost",		this,	"Cost",				7, 35,	true);
	Text numberLabelForRow		("RowOne",		this,	"1.",				8, 1,	true);

	//Selection descriptionSel("DescriptionSelection", this, 1, 30, 8, 3, true);


	supplierSel->populateData(database::select("SELECT name FROM supplier;"),1);
	/*descriptionSel.populateData(database::select(
				"SELECT description, code FROM equipment;"
				), 2);*/
}


void NewRental::addLine(bool repeatable)
{
	Text numberLabelForRow	("RowTwo", this, "2.", 9, 1, true);
}


void NewRental::handleInput(int ch)
{
	switch (ch)
	{
		case KEY_F(2):
			addLine(true);
			break;
		case 10:
			m_children[selectedChild]->Draw();
			m_children[selectedChild]->getData();
			nextChild();
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
