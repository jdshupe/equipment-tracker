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

class Element;
class Table : public Element
{
	private:
		int						m_selectedRows;
		int						m_dataRows;
		std::string					m_headers;
		std::string					m_query;
		std::vector<int>				m_widths;
		std::vector<std::vector<Cell*>>	m_cellMatrix;

		void draw();

		void createHeaderCells();

		void populateCellMatrix(std::string data);

		void drawHeaderRow(bool filerOn = false);

		void drawBodyRows();

		void createColumnWidths(std::string p_value);

	public:
		Table(Div* p_div, int p_rows, int p_cols, std::string p_headers, std::string p_widths = "none");

		void render();

		void refreshData();

		void rowDown();
		void rowUp();

		const std::string& query() const { return m_query; }
		void query(const std::string p_query) { m_query = p_query; }
};

#endif
