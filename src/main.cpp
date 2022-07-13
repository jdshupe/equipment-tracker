/* include statements */
#include <curses.h>
#include "div.h"
#include "divs/newRental.h"
#include "text.h"
#include "table.h"
#include <string>

using namespace std;

/* declarations */
int ch;

Div* activeWindow;

void startCurses();
void setColors();
void createNewRental();

/* main loop */
int main()
{
	startCurses();

	/* create windows */
	Div header_win("Rentals", 0, 0, LINES - 3, COLS);
	activeWindow = &header_win;
	Div footer_win("Key Bindings", LINES - 3, 0, 3, COLS);

	Text key_bind_1(&footer_win, 
			"F1:Quit  N:New Rental  F:Filter  E:Extend", 1, 2);

	string headers = "PO Number,Description,Price,Start Date,End Date ";
	string widths = "14,50,10,11,11";

	Table header_table(&header_win, LINES-6, COLS-2, 1, 1,  headers, widths);
	header_table.query("\
			SELECT \
				o.number as \"PO Number\",\
				e.description as \"Description\",\
				od.unit_cost as \"Price\",\
				o.start_date as \"Start Date\",\
				o.start_date + (o.rental_duration * o.cycle_length) as \"End Date\" \
			FROM purchase_order o \
			JOIN purchase_order_details od on od.purchase_order_id = o.id \
			JOIN equipment e on od.equipment_id = e.id \
				WHERE e.is_equipment");
	header_table.refreshData();

	wrefresh(header_win.win());
	wrefresh(footer_win.win());
	refresh();

	/* main loop */
	while((ch = getch()) != KEY_F(1))
	{
		if ( activeWindow == &header_win )
		{
			switch(ch)
			{
				case KEY_DOWN:
				case 'j':
					header_table.rowDown();
					header_win.render();
					header_table.render();
					break;
				case KEY_UP:
				case 'k':
					header_table.rowUp();
					header_win.render();
					header_table.render();
					break;
				case 'N':
					Text key_bind_2(&footer_win, 
						"F1:Cancel  F2:Add Monthly Line  F3:Add One Time Fee", 1, 2);
					NewRental rentalWindow("New Rental", 20, 60);
					activeWindow = &header_win;
					header_win.render();
					header_table.render();
					header_table.refreshData();
					footer_win.render();
					break;
			}
		} else {
		}
	};

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
}

