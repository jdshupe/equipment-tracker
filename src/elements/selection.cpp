// selection.cpp
#include "selection.h"
/* 
 * TODO(bug) remove the option window upon selection and redraw the screen
 */


/**
 * Class implementation for a form to hold multiple options and be search able.
 *
 * Contains a list of at least one data value that is sorted and displayed upon
 * typing into the main data display box. List can then be navigated and
 * selected from, updating the form to display the appropriate data.
 *
 * @param div the parent div where the object is drawn
 * @param height/width the number of lines/columns the selection display will use
 * @param yPos/xPos the coordinates of the top left corner of the selection box
 */
Selection::Selection(std::string name, std::string labelText, Div* div, int height, int width, int yPos, int xPos, bool hidden)
: Element(name, div, height, width, yPos, xPos, hidden)
{
	m_inputXPos = labelText.length() + xPos + 1;
	drawLabel(labelText);
}



void Selection::Draw()
{
	m_textLabel->Draw();
}


/**
 * Handles the keyinputs when object is active
 *
 * Currently has bindings for moving up and down the list, taking input of text
 * and making calls to update the data list, and handles the delete options.
 */
std::string Selection::getData()
{
	wchar_t ch;

	curs_set(1);									// make cursor visible
	keypad(m_div->win(), TRUE);						// enable keypad input for parent div

	wmove(m_div->win(), m_yPos, m_inputXPos + m_value.length());		// move cursor to starting location
	
	m_optionsWindow = createWindow();				// creates the dropdown window

	/**
	 * While loop to handle input
	 *
	 * Currently handles:
	 *		deleting,
	 *		navigating the displayed options,
	 *		and default typing
	 */
	while((ch = wgetch(m_div->win())) != 10)
	{
		switch (ch) {
			// cathces all deletion keys
			case KEY_BACKSPACE:
			case KEY_DC:
			case 127:
				// makes sure there is a value to be removed
				if (m_value.length() != 0) 
				{
					m_value.pop_back(); // removes last character

					/**
					 * this adds spaces to the end of the string in order to
					 * update and remove the deleted characters by printing a
					 * space over them
					 */
					std::string displayValue = m_value;
					displayValue.append(m_width - m_value.length(), ' ');

					// prints the updated value and moves the cursor one space
					wattron(m_div->win(), COLOR_PAIR(1));
					mvwprintw(m_div->win(), m_yPos, m_inputXPos, "%s", displayValue.c_str());
					wattroff(m_div->win(), COLOR_PAIR(1));
					wmove(m_div->win(), m_yPos, m_inputXPos + m_value.length());

					updateOptions();
				};
				break;
			// these 2 cases handle navigating the displayed list of options
			case KEY_UP:
				rowUp();
				wrefresh(m_optionsWindow);
				break;
			case KEY_DOWN:
				rowDown();
				wrefresh(m_optionsWindow);
				break;

			// This is the standard input handler,
			// catches all characters to update the search
			default:
				m_value += (ch); // add typed character to selection value
				updateOptions();
				wattron(m_div->win(), COLOR_PAIR(1));
				mvwprintw(m_div->win(), m_yPos, m_inputXPos, "%s", m_value.c_str());
				wattroff(m_div->win(), COLOR_PAIR(1));
				break;
		}	
	}
	/**
	 * The following lines handle making the actual selection. This involves
	 * printing it, removing the selection window, and passing the values
	 * associated to the rest of the form
	 */
	m_value = removeTrailingSpaces(m_displayedList[m_selectedOption-1][0]);

	wclear(m_optionsWindow);
	wrefresh(m_optionsWindow);
	delwin(m_optionsWindow);
	curs_set(0);									// hide cursor

	redrawwin(m_div->win());
	wattron(m_div->win(), COLOR_PAIR(1));
	mvwprintw(m_div->win(), m_yPos, m_inputXPos, "%s", m_value.c_str());
	wattroff(m_div->win(), COLOR_PAIR(1));
	
	return m_value.c_str();
}


/**
 * Refreshed the data options based on the current input text
 *
 * Pulls and displays the top x items in the data list that match the current 
 * input text. This is called any time the input text is updated. Send the 
 * matching items to a local window that is displayed and updated every call.
 * Has logic to handle highlighting the currently selected option.
 */
void Selection::updateOptions()
{
	int numberOfResults = 0; ///> holds row number to print each result
	werase(m_optionsWindow);
	wrefresh(m_optionsWindow);
	m_displayedList.clear();
	
	if(m_value != "")
	{
		for (int i = 0; i < m_dataList.size(); i++)
		{
			if (toLowerCase(m_dataList[i][0]).find(toLowerCase(m_value)) != std::string::npos)
			{
				m_displayedList.push_back(m_dataList[i]);
				// checks if the row being printed is the selected row and
				// changes colors appropriately
				m_selectedOption == numberOfResults + 1 ?
					wattron(m_optionsWindow, COLOR_PAIR(4)) :
					wattron(m_optionsWindow, COLOR_PAIR(3));	

				//TODO(bug) program crashes if deleting a character longer thatn the options window
				std::string printValue;
				if (m_dataList[i][0].length() > m_width)
				{
					printValue = m_dataList[i][0].substr(0,m_width);
				} else if (m_dataList[i][0].length() < m_width)
				{
					printValue = m_dataList[i][0].append(m_width - m_dataList[i][0].length(), ' ');
				} else {
					printValue = m_dataList[i][0];
				}
				mvwprintw(m_optionsWindow, numberOfResults, 0, "%s", printValue.c_str());

				wrefresh(m_optionsWindow);
				m_selectedOption == i + 1 ?
					wattroff(m_optionsWindow, COLOR_PAIR(4)): 
					wattroff(m_optionsWindow, COLOR_PAIR(3));	
				numberOfResults++;
			}
		}
	}
}


/**
 * Creates the window to hold the filtered data results prior to selection
 */
WINDOW* Selection::createWindow()
{
	WINDOW* local_win;

	local_win = newwin(5, m_width, m_yPos + 1 + m_div->yPos(), m_inputXPos + m_div->xPos());

	return local_win;
}

/*
 * when called, the following 2 functions increment/decrement as needed and then
 * reprint the lines with the appropriate colors. This goes as follows:
 * 1. reprint the currently highlighted line w/o color
 * 2. increment the selected line number
 * 3. reprint the new selected line w/ color
 * 4. refresh the screen
 */
void Selection::rowDown()
{
	// set font to black on white
	wattron(m_optionsWindow, COLOR_PAIR(3));
	// reprint old line without highlighting
	mvwprintw(m_optionsWindow, m_selectedOption-1, 0, "%s",
			m_displayedList[m_selectedOption-1][0].c_str());

	// increment and move to start if at end
	m_selectedOption == m_displayedList.size() ? 
		m_selectedOption = 1 : 
		m_selectedOption++; 

	// turn on green letters
	wattron(m_optionsWindow, COLOR_PAIR(4));
	// reprint new line with highlighting
	mvwprintw(m_optionsWindow, m_selectedOption-1, 0, "%s",
			m_displayedList[m_selectedOption-1][0].c_str());
	// set color back to default
	wattroff(m_optionsWindow, COLOR_PAIR(4));
}
void Selection::rowUp()  
{ 
	wattron(m_optionsWindow, COLOR_PAIR(3));
	mvwprintw(m_optionsWindow, m_selectedOption-1, 0, "%s",
			m_displayedList[m_selectedOption-1][0].c_str());

	m_selectedOption == 1 ? 
		m_selectedOption = m_dataList.size() : 
		m_selectedOption--; 

	wattron(m_optionsWindow, COLOR_PAIR(4));
	mvwprintw(m_optionsWindow, m_selectedOption-1, 0, "%s",
			m_displayedList[m_selectedOption-1][0].c_str());
	wattroff(m_optionsWindow, COLOR_PAIR(4));
}


/**
 * fills the datalist member with data
 *
 * @param data a comma separated list of data values
 * @param xDim the number of columns of data
 *
 * takes the data string and populates an array of arrays with length xDim
 */
void Selection::populateData(std::string data, int xDim)
{
	int yDimIncrement;
	int	xDimIncrement = 0;
	while (data.length() != 0)
	{
		xDimIncrement == 0 ? yDimIncrement = 0 : yDimIncrement = xDimIncrement / xDim;
		m_dataList.resize(yDimIncrement + 1);
		m_dataList[yDimIncrement].push_back(data.substr(0, data.find(",")));
		data.erase(0, data.find(",") + 1);
		xDimIncrement++;
	}
}


/**
 * returns an input string in all lower case letters
 *
 * @param string a string value
 */
std::string Selection::toLowerCase(std::string string) {
	std::transform(string.begin(), string.end(), string.begin(), ::tolower );
	return string;
}


std::string Selection::removeTrailingSpaces(std::string string) {
	const char* WhiteSpace = " \t\v\r\n";
	std::size_t start = string.find_first_not_of(WhiteSpace);
	std::size_t end = string.find_last_not_of(WhiteSpace);
	return start == end ? std::string() : string.substr(start, end - start + 1);
}



int Selection::highlight()
{
	m_textLabel->highlight();
	return 1;
}
