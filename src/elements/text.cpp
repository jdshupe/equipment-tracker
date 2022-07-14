// text.cpp
#include "text.h"

// TODO(ADD FUNCTIONALITY) add a width to the text box and make it so text scrolls if it goes over

using namespace std;

Text::Text(std::string name, Div* _div, string _text, int _y, int _x, int p_width)
: Element(name, _div, 1, p_width, _y, _x)
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
	char value[80];
	mvwgetstr(m_div->win(), m_yPos, lastCol() + 1, value);
	return std::string(value);
}

