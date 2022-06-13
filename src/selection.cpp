// selection.cpp
#include "selection.h"

Selection::Selection(Div* div, int height, int width, int yPos, int xPos)
: Element(div, height, width, yPos, xPos)
{

};

void Selection::makeSelection()
{
	noecho();
	curs_set(1);
	wmove(m_div->win(), m_yPos, m_xPos);
	int ch;

	while((ch = wgetch(m_div->win())) != 10)
	{
		switch (ch) {
			case KEY_BACKSPACE:
			case KEY_DC:
			case 127:
				// TODO(bug) if m_value is empty and delete is pressed it throws a segmentation error
				m_value.pop_back();
				mvwprintw(m_div->win(), m_yPos, m_xPos, "%s", m_value.c_str());
				wclrtoeol(m_div->win());
				break;
			default:
				m_value += (ch);
				mvwprintw(m_div->win(), m_yPos, m_xPos, "%s", m_value.c_str());
				break;
		}
	}
}

