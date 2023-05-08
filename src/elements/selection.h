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
		std::vector<std::vector<std::string>>	m_dataList;			// list of all data returned by the query
		std::vector<std::vector<std::string>>	m_displayedList;	// list of values that match current filter

		std::string		m_value;				// selected data value
		WINDOW*			m_optionsWindow;		// the window the filtered options are displayed in
		int				m_selectedOption = 1;	// initializes the selected option as the first one.
		std::string		m_query;				// the query used to populate the data
		Text*			m_textLabel;			// text label for the selection
		int				m_inputXPos;			// where text input begins. The label length.

		WINDOW* createWindow();


	public:
		Selection(std::string name, std::string labelText,  Div* div, int height, int width, int yPos, int xPos, bool hidden = false);

		void drawLabel(std::string text)
		{
			m_textLabel = new Text("Selection Label", m_div, text, m_yPos,
					m_xPos, true, text.length());
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
		std::string removeTrailingSpaces(std::string string);

		void Draw();

		int highlight();

		std::string value() { return m_value; }
};


#endif
