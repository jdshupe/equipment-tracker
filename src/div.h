// div.h
#ifndef DIV_H
#define DIV_H
#include <string>
#include <curses.h>
#include <vector>
#include "element.h"

class Element;
class Div
{
	private:
		std::string				m_name;
		int						m_xPos;
		int						m_yPos;
		int						m_height;
		int						m_width;
		WINDOW*					m_window;
		std::vector<Element*>	m_elements;

		WINDOW* createWindow();

		void draw();


	public:
		Div(std::string p_name, int p_y, int p_x, int p_height, int p_width);

		void render();

		void destroy_win();

		int height() { return m_height; };
		void height(int p_height) { m_height = p_height; };

		int width() { return m_width; };
		void width(int p_width) {m_width = p_width; };

		WINDOW* win() { return m_window; };
};

#endif
