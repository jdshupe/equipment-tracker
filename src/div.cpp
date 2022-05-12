// div.cpp
#include "div.h"

using namespace std;

Div::Div(string p_name, int p_y, int p_x, int p_height, int p_width)
{
	m_name			= p_name;
	m_xPos			= p_x;
	m_yPos			= p_y;
	m_height		= p_height;
	m_width			= p_width;

	m_window		= Div::createWindow();

	draw();
}

WINDOW* Div::createWindow()
{
	WINDOW* local_win;

	local_win = newwin(m_height, m_width, m_yPos, m_xPos);
	box(local_win, 0, 0);

	return local_win;
}

void Div::draw()
{
	box(m_window, 0, 0);
	mvwprintw(m_window, 0, 1, "%s", m_name.c_str());
	wrefresh(m_window);
}


void Div::render()
{
	draw();
}

void Div::destroy_win()
{
	wborder(m_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(m_window);
	delwin(m_window);
}
