// selection.h
#ifndef SELECTION_H
#define SELECTION_H

#include <algorithm>
#include <cctype>
#include "../element.h"
#include "text.h"
#include <vector>
#include <string>
#include "../connection.h"

class Selection : public Element
{
	private:
		std::vector<std::vector<std::string>>	m_dataList;
		std::vector<std::vector<std::string>>	m_displayedList;
		std::string								m_value;
		WINDOW*									m_optionsWindow;
		int										m_selectedOption = 1;
		std::string								m_query;
		Text*									m_textLabel;

		WINDOW* createWindow();


	public:
		Selection(std::string name, Div* div, int height, int width, int yPos, int xPos, bool hidden = false);

		void drawLabel()
		{
			m_textLabel = new Text("Selection Label", m_div, m_name.append(":") , m_yPos,
					m_xPos, true, m_name.length());
		}

		std::string getData();

		void populateData(std::string data, int xDim);

		void updateOptions();

		void rowDown();
		void rowUp();

		// get/set for selection data query
		const std::string& query() const { return m_query; }
		void query(const std::string query) { m_query = query; }

		std::string toLowerCase(std::string string);

		void Draw();

		int highlight();
};


#endif
