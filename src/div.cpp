// div.cpp
#include "div.h"
#include <iostream>

using namespace std;

Div::Div(string name, int yPos, int xPos, int height, int width)
{
	m_name			= name;
	m_yPos			= yPos;
	m_xPos			= xPos;
	m_height		= height;
	m_width			= width;

	m_window		= Div::createWindow();

	draw();
}

Div::Div(string name, int height, int width)
{
	m_name			= name;
	m_yPos			= (LINES - height) / 2;
	m_xPos			= (COLS - width) / 2;
	m_height		= height;
	m_width			= width;

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

void Div::addChild(Element* elementToAdd)
{
	m_children.push_back(elementToAdd);
}

//TODO this function is to find a child of a div by its name. For some reason, this no work.
Element* Div::child(std::string name)
{
}
