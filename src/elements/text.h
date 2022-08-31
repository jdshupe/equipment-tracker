// text.h
#ifndef TEXT_H
#define TEXT_H

#include "../element.h"

class Text : public Element
{
	private:
		std::string		m_text;
		std::string		m_displayedText;

	public:
		Text(std::string name, Div* p_div, std::string p_text, int p_y, int p_x, bool hidden = false, int p_width = 0);

		void		Draw();
		std::string getData();
		int			highlight();

		WINDOW* win() { return m_div->win(); }
		
		int lastCol() { return m_width + m_xPos; }

};

#endif
