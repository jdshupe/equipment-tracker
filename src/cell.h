// cell.h
#ifndef CELL_H
#define CELL_H

#include <curses.h>
#include <string>

/**
 * Data unit to build methods on.
 * 
 * The purpose is to enable easy addition of common methods and properties that would not be possible
 * with the core data types. 
 * Currently only in use with the table class but can be used elsewhere to provide better data access.
 */
class Cell
{
	private:
		std::string		m_value;
	
	public:
		Cell(std::string value);

		// get/set for cell value
		std::string		getValue() { return m_value; };
		void			setValue(std::string p_value) { m_value = p_value; };
};

#endif
