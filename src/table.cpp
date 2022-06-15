// table.cpp
#include "table.h"

using namespace std;

Table::Table(Div* div, int height, int width, int yPos, int xPos, string headers, string widths) 
: Element(div, height, width, yPos, xPos)
{
	m_headers		= headers;
	m_selectedRow	= 1;

	createColumnWidths(widths);

	/**TODO[refactor] the number of rows in the cell matrix should be based of off the data returned
	 * not the height of the div. This will enable row scrolling instead of having to requery data
	 * every time the page is scrolled.
	 */
	m_cellMatrix.resize(height);
	for (size_t i = 0; i < height; i++) m_cellMatrix[i].resize(m_widths.size());

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

	for(int i = 0; i < count(m_headers.begin(), m_headers.end(), ',') + 1; i++) // for loop to create cells
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
	for (int y = 1; y < m_height; y++)
	{
		for (int x = 0; x < m_widths.size(); x++)
		{
			m_cellMatrix[y][x] = new Cell(data.substr(0, data.find(",")));
			data.erase(0, data.find(",") + 1);
		}
	}
}

void Table::drawHeaderRow(bool filterOn)
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

void Table::createColumnWidths(string widths)
{
	int numberOfColumns = count(m_headers.begin(), m_headers.end(), ',') + 1; /** number of columns is the number 
																				of ',' in the string plus one to
																				catch the last value */
	if(widths == "none")
	{
		for(int i = 0; i < numberOfColumns; i++)
		{
			m_widths.push_back((COLS-1)/numberOfColumns);
		}
	} else 
	{
		for(int i = 0; i < numberOfColumns; i++)
		{
			m_widths.push_back(stoi(widths.substr(0, widths.find(","))));
			widths.erase(0, widths.find(",") + 1);
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

void Table::rowDown(){ m_selectedRow == m_dataRows ? m_selectedRow = 1 : m_selectedRow++; }

void Table::rowUp(){ m_selectedRow == 1 ? m_selectedRow = m_dataRows : m_selectedRow--; }
