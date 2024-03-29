/* include statements */
#include <curses.h>
#include "div.h"
#include "divs/newRental.h"
#include "divs/homePage.h"
#include <string>
#include "elements/table.h"
#include "elements/text.h"

using namespace std;

/* declarations */
int ch; // var that holds key inputs for the main loop

Div* activeWindow; // var that holds a pointer to window currently taking input
HomePage* header_win; // the main screen


/* Initialization */
void startCurses();
void setColors();


/* main function */
int main()
{
	startCurses();

	/* create windows */
	header_win = new HomePage("Rentals", 0, 0, LINES - 3, COLS);
	activeWindow = header_win;
	Div footer_win("Key Bindings", LINES - 3, 0, 3, COLS);

	Text key_bind_1("KeyBinds", &footer_win, 
			"F1:Quit  N:New Rental  F:Filter  E:Extend", 1, 2);

	wrefresh(header_win->win());
	wrefresh(footer_win.win());
	refresh();

	/* main loop */
	while((ch = getch()) != KEY_F(1))
	{
		activeWindow->handleInput(ch);
	}

	endwin();
	return 0;
}


/* stores all the initialization for curses */
void startCurses() 
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	refresh();
	curs_set(0);
	if (has_colors())
	{
		use_default_colors();
		start_color();
		setColors();
	}
}

void setColors()
{
	init_color(8, 700, 700, 700);

	init_pair(1, COLOR_GREEN, -1);
	init_pair(2, 8, -1);
	init_pair(3, 8, COLOR_WHITE);
	init_pair(4, COLOR_GREEN, COLOR_WHITE);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
}
