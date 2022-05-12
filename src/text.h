// text.h
#ifndef TEXT_H
#define TEXT_H

#include <curses.h>
#include <string>
#include "div.h"

class Text
{
	private:
		std::string		m_text;
		std::string		m_displayedText;
		int			m_xPos, m_yPos;
		int			m_width;
		Div*		div;

	public:
		Text(Div* p_div, std::string p_text, int p_y, int p_x);

		void Draw();

		WINDOW* win() { return div->win(); }
		
		int lastCol() { return m_width + m_xPos; }
};

#endif
