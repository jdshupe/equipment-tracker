// text.cpp
#include "text.h"

// TODO(ADD FUNCTIONALITY) add a width to the text box and make it so text scrolls if it goes over
// TODO(ADD FUNCTIONALITY) create input method that records and displays input text

using namespace std;

Text::Text(Div* _div, string _text, int _y, int _x)
{
	m_text = _text;
	m_yPos = _y;
	m_xPos = _x;
	m_div = _div;

	Draw();
}

void Text::Draw()
{
	m_text.length() > m_width ? m_displayedText = (m_text.substr(0, m_width - 2) + "..") : m_displayedText = m_text;
	mvwprintw(m_div->win(), m_yPos, m_xPos, "%s", m_displayedText.c_str());
	wrefresh(m_div->win());
};
