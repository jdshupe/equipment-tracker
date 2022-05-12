// text.cpp
#include "text.h"

// TODO(ADD FUNCTIONALITY) add a width to the text box and make it so text scrolls if it goes over
// TODO(ADD FUNCTIONALITY) create input method that records and displays input text

using namespace std;

Text::Text(Div* _div, string _text, int _y, int _x)
{
	text = _text;
	y_pos = _y;
	x_pos = _x;
	div = _div;

	Draw();
}

void Text::Draw()
{
	text.length() > m_width ? m_displayedText = (text.substr(0, m_width - 2) + "..") : m_displayedText = text;
	mvwprintw(div->win(), y_pos, x_pos, "%s", m_displayedText.c_str());
	wrefresh(div->win());
};
