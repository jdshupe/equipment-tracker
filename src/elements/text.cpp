// text.cpp
#include "text.h"

// TODO(ADD FUNCTIONALITY) add a width to the text box and make it so text scrolls if it goes over

using namespace std;

Text::Text(std::string name, Div* _div, string _text, int _y, int _x, bool hidden, int p_width)
: Element(name, _div, 1, p_width, _y, _x, hidden)
{
	m_text = _text;
	p_width == 0 ? m_width = m_text.length() : m_width = p_width;

	Draw();
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
					m_displayedValue.append(30 - m_value.length(), ' ');

					mvwprintw(m_div->win(), m_yPos, m_xPos + m_displayedText.length(), 
							"%s", m_displayedValue.c_str());
					wmove(m_div->win(), m_yPos, m_xPos + m_displayedText.length() + m_value.length());
				}
				break;
			default:
				m_value += ch;
				mvwprintw(m_div->win(), m_yPos, m_xPos + m_text.length(), "%s", m_value.c_str());
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
