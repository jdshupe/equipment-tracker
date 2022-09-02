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
	// echo input and turn on cursor
	echo();
	curs_set(1);

	// turn to green on black color
	wattron(m_div->win(), COLOR_PAIR(1));

	char value[80];
	mvwgetstr(m_div->win(), m_yPos, lastCol() + 1, value);

	// turn to white on black color
	wattroff(m_div->win(), COLOR_PAIR(1));
	// turn off echo and cursor
	curs_set(0);
	noecho();

	return std::string(value);
}


// change to black on white and redraw
int Text::highlight()
{
	wattron(m_div->win(), COLOR_PAIR(5));
	Draw();
	wattroff(m_div->win(), COLOR_PAIR(5));
	return 1;
}
