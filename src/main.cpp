/* include statements */
#include <curses.h>
#include "div.h"
#include "divs/newRental.h"
#include <string>
#include "elements/table.h"
#include "elements/text.h"

using namespace std;

/* declarations */
extern int ch;
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

	Text key_bind_1("KeyBinds", &footer_win, 
			"F1:Quit  N:New Rental  F:Filter  E:Extend", 1, 2);

	string headers = "PO Number,Description,Price,Start Date,End Date ";
	string widths = "14,50,10,11,11";

	Table header_table("MainTable", &header_win, LINES-6, COLS-2, 1, 1,  headers, widths);
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
		activeWindow->handleInput(ch);
		/**TODO (refactor) update the input loop to sit inside the div class. This will
		 * then only have to call to the class input function based on what window is
		 * active. Should be able to do something like activeWindow->input().
		 */
		/*if (activeWindow == &header_win)
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
					Text key_bind_2("KeyBinds", &footer_win, 
						"F1:Cancel  F2:Add Monthly Line  F3:Add One Time Fee", 1, 2);
					NewRental rentalWindow("New Rental", 20, 60);
					activeWindow = &rentalWindow;
					break;
			}
		} else {
		}*/
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
}
