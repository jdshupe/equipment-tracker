// cell.h
#ifndef CELL_H
#define CELL_H

#include <curses.h>
#include <string>

class Cell
{
	private:
		std::string		m_value;
	
	public:
		Cell(std::string value);

		std::string		getValue() { return m_value; };
		void			setValue(std::string p_value) { m_value = p_value; };
};

#endif
