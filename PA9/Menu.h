#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

class Menu
{
public:

	Menu(sf::Vector2f size)
	{
		//Somewhat transparent window to darken background
		mOverlay.setSize(size);
		mOverlay.setFillColor(sf::Color(0, 0, 0, 150)); //150 is the alpha value; makes it transparent
	}

	virtual ~Menu() {}

	virtual void update(const sf::Vector2f& mousePosition) = 0; //For updating button state based on mouse position
	virtual void drawWindow(sf::RenderWindow& window) = 0; //For drawing the button and menu to screen 

protected:
	sf::RectangleShape mOverlay;

};