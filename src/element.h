// element.h
#ifndef ELEMENT_H
#define ELEMENT_H

#include <curses.h>
#include "div.h"
#include <string>
#include <iostream>

class Div;
class Element
{
	protected:
		Div*			m_div;
		int				m_width, m_height;
		int				m_xPos, m_yPos;
		std::string		m_name;
		bool			m_hidden;

	public:
		Element(std::string name, Div* div, int height, int width, int yPos, int xPos, bool hidden = false);
		std::string m_headers;

		int		height()			{ return m_height; }
		void	height(int height)	{ m_height = height; }

		int		width()				{ return m_width; }
		void	width(int width)	{ m_width = width; }

		Div*	div() const			{ return m_div; }
		void	div(Div* div)		{ m_div = div; }

		std::string name()					{ return m_name; }
		void		name(std::string name)	{ m_name = name; }

		void print()
		{
			std::cout << m_width << std::endl;
			std::cout << m_height << std::endl;
			std::cout << m_xPos << m_yPos << std::endl;
			std::cout << m_name << std::endl;
		}

		virtual void Draw(){};

		// virtual method for table derived class
		virtual void rowDown(){};
		virtual void rowUp(){};
		virtual void render(){};

		// virtual method for text derived class
		virtual std::string getData(){return "Not a derived Member";};
		virtual int			highlight(){return 0;};

		// virtual method for selection derived class
		virtual void makeSelection(){};
};

#endif
