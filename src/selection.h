// selection.h
#ifndef SELECTION_H
#define SELECTION_H

#include "element.h"
#include <vector>
#include <string>

class Selection : public Element
{
	private:
		std::vector<std::vector<std::string>>		m_dataList;
		std::string									m_value;

	public:
		Selection(Div* div, int height, int width, int yPos, int xPos);

		void makeSelection();

		void makeDataList(std::string dataString);

		void updateOptions();
};

#endif
