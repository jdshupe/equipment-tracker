// selection.cpp
#include "selection.h"

Selection::Selection(Div* div, int height, int width, int yPos, int xPos)
: Element(div, height, width, yPos, xPos)
{
	m_dataList = {{"Delivery","EQ- Delivery"},{"Pick Up","EQ- Pick Up"}};
	m_selectedOption = 1;

};

void Selection::makeSelection()
{
	noecho();
	curs_set(1);
	keypad(m_div->win(), TRUE);
	wmove(m_div->win(), m_yPos, m_xPos);
	m_optionsWindow = createWindow();
	wchar_t ch;

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
				};
				break;
			case KEY_UP:
				rowUp();
				updateOptions();
				break;
			case KEY_DOWN:
				rowDown();
				updateOptions();
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
				if(m_selectedOption == numberOfResults + 1)
				{
					wattron(m_optionsWindow, COLOR_PAIR(4));
				} else {
					wattron(m_optionsWindow, COLOR_PAIR(3));	
				}

				mvwprintw(m_optionsWindow, numberOfResults, 0, "%s", m_dataList[i][0].c_str());
				wrefresh(m_optionsWindow);
				m_selectedOption == i + 1 ? wattroff(m_optionsWindow, COLOR_PAIR(4)): wattroff(m_optionsWindow, COLOR_PAIR(3));	
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

void Selection::rowDown(){ m_selectedOption == m_dataList.size() ? m_selectedOption = 1 : m_selectedOption++; }
void Selection::rowUp()  { m_selectedOption == 1 ? m_selectedOption = m_dataList.size() : m_selectedOption--; }
