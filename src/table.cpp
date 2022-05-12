// table.cpp
#include "table.h"

using namespace std;

Table::Table(Div* p_div, int p_rows, int p_cols, string p_headers, string p_widths = "none") : Element(p_div, p_rows, p_cols)
{
	m_headers		= p_headers;
	m_selectedRow	= 1;

	m_cellMatrix.resize(p_rows);
	for (size_t i = 0; i < p_rows; i++) m_cellMatrix[i].resize(p_cols);

	createColumnWidths(p_widths);
	createHeaderCells();
}

void Table::draw()
{
	drawHeaderRow();
	drawBodyRows();
}

void Table::createHeaderCells()
{
	string temp_header = m_headers;

	for(int i = 0; i < m_cols; i++) // for loop to create cells
	{
		m_cellMatrix[0][i] = new Cell(temp_header.substr(0, temp_header.find(",")));
		temp_header.erase(0, temp_header.find(",") + 1); // remove value from string
	}
}

void Table::populateCellMatrix(string data)
/**
 * breaks the returned query data in the cells for the table
 *
 * @param data a string containing comma separated values
 */
{
	// TODO need to clear the matrix prior to loading in data.
	// This will be similar to initializing it
	for (int y = 1; y < m_rows; y++)
	{
		for (int x = 0; x < m_cols; x++)
		{
			m_cellMatrix[y][x] = new Cell(data.substr(0, data.find(",")));
			data.erase(0, data.find(",") + 1);
		}
	}
}

void Table::drawHeaderRow(bool filterOn = false)
{
	int lastPosition = 1;
	for(int i = 0; i < m_cellMatrix[0].size(); i++)
	{
		wattron(m_div->win(), A_UNDERLINE);
		string value = m_cellMatrix[0][i]->getValue();

		string paddedValue = value.append(m_widths[i] - value.length() - 1, ' ');
		mvwprintw(m_div->win(),1, lastPosition, "%s|", paddedValue.c_str());
		// if the filter is on it highlights the first 2 letters
		if (filterOn)
		{
			wattron(m_div->win(), A_STANDOUT);
			mvwaddch(m_div->win(), 1, lastPosition, value[0]);
			wattroff(m_div->win(), A_STANDOUT);
		}
		lastPosition += m_widths[i];
		wattroff(m_div->win(), A_UNDERLINE);
	}
	wrefresh(m_div->win());
}

void Table::drawBodyRows()
{
	for (int y = 1; y < m_cellMatrix.size(); y++)
	{
		int lastPosition = 1;
		for (int x = 0; x < m_cellMatrix[y].size(); x++)
		{
			if (m_selectedRow == y) wattron(m_div->win(),COLOR_PAIR(1)); // checks if the current line is the selected one and turns on highlighting
			string value = m_cellMatrix[y][x]->getValue();
			if (value.length() > m_widths[x]) value = value.substr(0, m_widths[x]-3) + ".. "; // pads the string with '.. ' if the value is longer than the column width
			mvwprintw(m_div->win(), y + 1, lastPosition, "%s", value.c_str());
			lastPosition += m_widths[x];
			if (m_selectedRow == y) wattroff(m_div->win(),COLOR_PAIR(1)); // turns of color if it was tunred on.
		}
	}
	wrefresh(m_div->win());
}

void Table::createColumnWidths(string _widths)
{
	if(_widths == "none")
	{
		for(int i = 0; i < m_cols; i++)
		{
			m_widths.push_back((COLS-1)/m_cols);
		}
	} else 
	{
		for(int i = 0; i < m_cols; i++)
		{
			m_widths.push_back(stoi(_widths.substr(0, _widths.find(","))));
			_widths.erase(0, _widths.find(",") + 1);
		}
	}
}

void Table::render()
{
	draw();
}

void Table::refreshData()
{
	populateCellMatrix(database::select(m_query, &m_dataRows));
	draw();
}

void Table::rowDown()
{
	m_selectedRow == m_dataRows ? m_selectedRow = 1 : m_selectedRow++;
}

void Table::rowUp()
{
	m_selectedRow == 1 ? m_selectedRow = m_dataRows : m_selectedRow--;
}
