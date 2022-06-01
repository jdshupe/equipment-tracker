// selection.cpp
#include "selection.h"

Selection::Selection(Div* div, int height, int width, int yPos, int xPos)
: Element(div, height, width, yPos, xPos)
{

};

void Selection::makeSelection()
{
	echo();
	curs_set(1);
	int ch;

	while(ch != 10)
	{
		m_value += mvwgetch(m_div->win(), m_yPos, m_xPos + m_value.length());
		mvwprintw(m_div->win(), 15, 15, m_value.c_str() );
	}
}

