// text.cpp
#include "text.h"

// TODO(ADD FUNCTIONALITY) add a width to the text box and make it so text scrolls if it goes over
// TODO(refactor) remove the width default and use the constructor without the
// value to auto fit.

/*
 * Class implementation for the Text element which is the default data holder.
 *
 * This acts as a freeform data input. Currently has the option to hold data, or 
 * have a label. 
 *
 * @param name		the string by which the element is refered
 * @param div		the parent div where the object is drawn
 * @param label		string value of an optional label. Drawn at the specified x
 *					coordinate. Data input will begin 1 col after the label
 * @param y/x		the coordinates of the first letter of the label
 * @param hidden	if the element should be accessible on the tree of the
 *					parent div (default = false)
 * @param width		limits the width of the data input area, useful if another
 *					element is placed in the same row. prevents input value from
 *					bleeding over
 * 
 * @member m_text	stores the input value as a string
 */
Text::Text(std::string name, Div* _div, std::string label, int _y, int _x, bool hidden, int p_width)
: Element(name, _div, 1, p_width, _y, _x, hidden)
{
	m_text = label;
	p_width == 0 ? m_width = m_text.length() : m_width = p_width;

	Draw();
	m_inputXPos = m_xPos + m_displayedText.length() + 1;
}


void Text::Draw()
{
	m_text.length() > m_width ? m_displayedText = (m_text.substr(0, m_width - 2) + "..") : m_displayedText = m_text;
	mvwprintw(m_div->win(), m_yPos, m_xPos, "%s", m_displayedText.c_str());
	wrefresh(m_div->win());
};


std::string Text::getData()
{
	// inital setup
	wmove(m_div->win(), m_yPos, m_inputXPos + m_value.length());
	curs_set(1);
	wattron(m_div->win(), COLOR_PAIR(1)); // turn to green on black color

	// input handle
	int ch;
	while ( (ch = wgetch(m_div->win())) != 10)
	{
		switch (ch)
		{
			case KEY_BACKSPACE:
			case KEY_DC:
			case 127:
				if (m_value.length() != 0)
				{
					m_value.pop_back();
					m_displayedValue = m_value;
					m_displayedValue.append(m_width - m_value.length(), ' ');

					mvwprintw(m_div->win(), m_yPos, m_inputXPos, 
							"%s", m_displayedValue.c_str());
					wmove(m_div->win(), m_yPos, m_inputXPos + m_value.length());
				}
				break;
			default:
				m_value += ch;
				mvwprintw(m_div->win(), m_yPos, m_inputXPos, "%s", m_value.c_str());
				break;
		}
	}

	// turn off input settings
	wattroff(m_div->win(), COLOR_PAIR(1)); // turn to white on black color
	curs_set(0);

	return std::string(m_value);
}


// change to black on white and redraw
int Text::highlight()
{
	wattron(m_div->win(), COLOR_PAIR(5));
	Draw();
	wattroff(m_div->win(), COLOR_PAIR(5));
	return 1;
}
