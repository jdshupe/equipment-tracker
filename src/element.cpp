// element.cpp
#include "element.h"

Element::Element(std::string name, Div* div, int height, int width, int yPos, int xPos)
{
	m_name		= name;
	m_div		= div;
	m_height	= height;
	m_width		= width;
	m_yPos		= yPos;
	m_xPos		= xPos;

	m_div->addChild(m_name, this);
};
