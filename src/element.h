// element.h
#ifndef ELEMENT_H
#define ELEMENT_H

#include <curses.h>
#include "div.h"

class Div;
class Element
{
	protected:
		Div*			m_div;
		int				m_rows, m_cols;

	public:
		Element(Div* p_div, int p_rows, int p_cols);

		int rows() { return m_cols; }
		void rows(int p_rows) { m_rows = p_rows; }

		int cols() { return m_cols; }
		void cols(int p_cols) { m_cols = p_cols; }

		Div* div() const { return m_div; }
		void div(Div* p_div) { m_div = p_div; }
};

#endif
