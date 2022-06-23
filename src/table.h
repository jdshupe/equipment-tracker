// table.h
#ifndef TABLE_H
#define TABLE_H

#include "cell.h"
#include "connection.h"
#include <string>
#include <curses.h>
#include <iostream>
#include <vector>
#include "element.h"
#include <algorithm>

class Cell;
class Element;
class Table : public Element
{
	private:
		int									m_selectedRow;
		int									m_dataRows;
		std::string							m_headers;
		std::string							m_query;
		std::vector<int>					m_widths;
		std::vector<std::vector<Cell*>>		m_cellMatrix;

		void draw();

		void createHeaderCells();

		void populateCellMatrix(std::string data);

		void drawHeaderRow(bool filerOn = false);

		void drawBodyRows();

		void createColumnWidths(std::string value);

	public:
		Table(Div* div, int height, int width, int yPos, int xPos, std::string headers, std::string widths = "none");

		void render();

		void refreshData();

		void rowDown();
		void rowUp();

		// get/set for the table query
		const std::string& query() const { return m_query; }
		void query(const std::string query) { m_query = query; }
};

#endif
