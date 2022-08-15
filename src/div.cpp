// div.cpp
#include "div.h"

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


void Div::handleInput(int ch)
{
	switch(ch)
	{
		case KEY_DOWN:
		case 'j':
			child("MainTable")->rowDown();
			child("MainTable")->render();
			break;
		case KEY_UP:
		case 'k':
			child("MainTable")->rowUp();
			child("MainTable")->render();
			break;
	/*	case 'N':
			NewRental rentalWindow("New Rental", 20, 60);
			activeWindow = &rentalWindow;
			break;*/
	}
}


Element* Div::child(std::string name)
{
	for (int i = 0; i < m_children.size(); i++)
	{
		if (m_children[i]->name() == name)
		{
			return m_children[i];
		} else {
		}
	}
}
