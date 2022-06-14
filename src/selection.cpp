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
	m_optionsWindow = createWindow();
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
					std::string displayValue = m_value;
					displayValue.append(m_width - m_value.length(), ' ');
					mvwprintw(m_div->win(), m_yPos, m_xPos, "%s", displayValue.c_str());
					wmove(m_div->win(), m_yPos, m_xPos + m_value.length());
					updateOptions();
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
	int numberOfResults = 0; ///> holds row number to print each result
	werase(m_optionsWindow);
	wrefresh(m_optionsWindow);
	
	if(m_value != "")
	{
		for (int i = 0; i < m_dataList.size(); i++)
		{
			if (m_dataList[i][0].find(m_value) != std::string::npos)
			{
				wattron(m_optionsWindow, COLOR_PAIR(3));	
				mvwprintw(m_optionsWindow, numberOfResults, 0, "%s", m_dataList[i][0].c_str());
				wrefresh(m_optionsWindow);
				wattroff(m_optionsWindow, COLOR_PAIR(3));	
				numberOfResults++;
			}
		}
	}
}

WINDOW* Selection::createWindow()
{
	WINDOW* local_win;

	local_win = newwin(5, m_width, m_yPos + 1 + m_div->yPos(), m_xPos + m_div->xPos());

	return local_win;
}


