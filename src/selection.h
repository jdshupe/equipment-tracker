// selection.h
#ifndef SELECTION_H
#define SELECTION_H

#include "element.h"
#include <vector>
#include <string>
#include "connection.h"

class Selection : public Element
{
	private:
		std::vector<std::vector<std::string>>	m_dataList;
		std::string								m_value;
		WINDOW*									m_optionsWindow;
		int										m_selectedOption;

		WINDOW* createWindow();

	public:
		Selection(Div* div, int height, int width, int yPos, int xPos);

		void makeSelection();

		void populateData(std::string data, int xDim);

		void updateOptions();

		void rowDown();
		void rowUp();
};

#endif
