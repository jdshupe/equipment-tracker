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
		int				m_width, m_height;
		int				m_xPos, m_yPos;

	public:
		Element(Div* div, int height, int width, int yPos, int xPos);

		int height() { return m_height; }
		void height(int height) { m_height = height; }

		int width() { return m_width; }
		void width(int width) { m_width = width; }

		Div* div() const { return m_div; }
		void div(Div* div) { m_div = div; }
};

#endif
