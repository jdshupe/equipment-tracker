// selection.cpp
#include "selection.h"

Selection::Selection(Div* div, int height, int width, int yPos, int xPos)
: Element(div, height, width, yPos, xPos)
{
	m_dataList = {{"Delivery","EQ- Delivery"},{"Pick Up","EQ- Pick Up"}};

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
				if (m_value.length() != 0) 
				{
					m_value.pop_back();
					mvwprintw(m_div->win(), m_yPos, m_xPos, "%s", m_value.c_str());
					wclrtoeol(m_div->win());
				}
				break;
			default:
				m_value += (ch);
				updateOptions();
				mvwprintw(m_div->win(), m_yPos, m_xPos, "%s", m_value.c_str());
				break;
		}
	}
}

void Selection::updateOptions()
// TODO(addition) display results in their own window so the whole window can be deleted on selection
{
	int numberOfResults;
	for (int i = 0; i < m_dataList.size(); i++)
	{
		if (m_dataList[i][0].find(m_value) != std::string::npos)
		{
			wattron(m_div->win(), COLOR_PAIR(2));	
			mvwprintw(m_div->win(), m_yPos + numberOfResults, m_xPos, "%s", m_dataList[i][0].c_str());
			wclrtoeol(m_div->win());
			wattroff(m_div->win(), COLOR_PAIR(2));	
			numberOfResults++;
		} else {
			wclrtoeol(m_div->win());
		}

	}
}

WINDOW* Selection::createWindow()
{
	WINDOW* local_win;

	local_win = newwin(5, m_width, m_yPos + 1, m_xPos);

	return local_win;
}


