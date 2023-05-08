// text.h
#ifndef TEXT_H
#define TEXT_H

#include "../element.h"

class Text : public Element
{
	private:
		std::string		m_value, m_displayedValue;
		std::string		m_text;
		std::string		m_displayedText;

		int		m_inputXPos;

	public:
		Text(std::string name, Div* div, std::string label,	int y, int x, bool hidden = false, int width = 0);
		//Text(std::string name, Div* div, std::string label, int y, int x, int width = 0);
		//Text(std::string name, Div* div, int y, int x, int width = 0, bool hidden = false);
		//Text(std::string name, Div* div, int y, int x, int width = 0);

		void		Draw();
		std::string getData();
		int			highlight();

		WINDOW* win() { return m_div->win(); }
		
		int lastCol() { return m_width + m_xPos; }

		std::string value() { return m_value; }

};

#endif
