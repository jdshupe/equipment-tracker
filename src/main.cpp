/* include statements */
#include <curses.h>
#include "div.h"
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

	Text key_bind_1(&footer_win, "F1:Quit", 1, 2);
	Text key_bind_2(&footer_win, "N:New Rental", 1, key_bind_1.lastCol() + 2);
	Text key_bind_3(&footer_win, "F:Filter", 1, key_bind_2.lastCol() + 2);
	Text key_bind_4(&footer_win, "E:Extend", 1, key_bind_3.lastCol() + 2);

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
					createNewRental();
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
	init_pair(1, COLOR_GREEN, -1);
}

void createNewRental()
{
	char s_poNumber[80], s_supplier[80], s_duration[10], s_length[10], s_startDate[80];
	char s_description[80], s_code[80], s_cost[80];
	string sqlNewPO;
	string sqlRentalDetail;

	Div newRentalWindow("New Rental", 3, 3, LINES-6, COLS-6); // create new div
	activeWindow = &newRentalWindow;

	Text po_number(&newRentalWindow, "PO Number:", 1, 2); // input line for PO number
	Text supplier( &newRentalWindow, "Supplier:",  2, 2);
	Text duration( &newRentalWindow, "Duration:",  3, 2);
	Text length(   &newRentalWindow, "Cycle Length:", 4, 2);
	Text startDate(&newRentalWindow, "Start Date:", 5, 2);

	mvwprintw(newRentalWindow.win(), 7, 2, "Description");
	mvwprintw(newRentalWindow.win(), 7, 50, "Code");
	mvwprintw(newRentalWindow.win(), 7, 65, "Cost");

	echo();
	curs_set(1);

	mvwgetstr(newRentalWindow.win(), 1, po_number.lastCol() + 2, s_poNumber);
	mvwgetstr(newRentalWindow.win(), 2, supplier.lastCol() + 2, s_supplier);
	mvwgetstr(newRentalWindow.win(), 3, duration.lastCol() + 2, s_duration);
	mvwgetstr(newRentalWindow.win(), 4, length.lastCol() + 2, s_length);
	mvwgetstr(newRentalWindow.win(), 5, startDate.lastCol() + 2, s_startDate);

	sqlNewPO = string(
			"INSERT INTO purchase_order (\
				number,\
				supplier_id,\
				rental_duration,\
				cycle_length)\
			VALUES (\
				'") + s_poNumber + string("',\
				(SELECT id FROM supplier WHERE name ='") + s_supplier + string("'),")
				+ s_duration + string(",")
				+ s_length + string(");");

	sqlRentalDetail = string(
			"INSERT INTO purchase_order_details(purchase_order_id, equipment_id, line_number, description)"
				"VALUES("
					"(SELECT id FROM purchase_order WHERE number = '") + s_poNumber + string("'),"
					"(SELECT id FROM equipment WHERE code = '");


	mvwgetstr(newRentalWindow.win(), 8, 2, s_description);
	mvwgetstr(newRentalWindow.win(), 8, 50, s_code);
	mvwgetstr(newRentalWindow.win(), 8, 65, s_cost);

	noecho();
	curs_set(0);
	database::insert(sqlNewPO);
	newRentalWindow.destroy_win();
	clear();
	refresh();
}
