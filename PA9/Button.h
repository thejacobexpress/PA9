#pragma once
#include <SFML/Graphics.hpp>

enum ButtonState
{
	Idle = 0, Hover = 1, Pushed = 2, Locked = 3
};

class Button : public sf::Sprite
{
public:

	Button(const sf::Texture& texture, sf::Vector2f position = { 0, 0 }, sf::Color idleColour = {sf::Color(0, 0, 0)}, sf::Color hoverColour = {sf::Color(100, 100, 100)}, sf::Color pushedColour = {sf::Color(150, 150, 150)}) : sf::Sprite(texture) //Default values to make visual studio happy
	{
		//Position
		setPosition(position);

		//Sprite
		mIdleColour = idleColour;
		mHoverColour = hoverColour;
		mPushedColour = pushedColour;

		//Set the defualt state
		mState = ButtonState::Idle;
		setColor(mIdleColour);
	}

	void setLocked(bool locked);
	bool isLocked(void) const;

	bool contains(const sf::Vector2f& mousePosition);
	void updateButtonState(const sf::Vector2f& mousePosition, bool isMousePressed);
	ButtonState getState() const;

private:
	ButtonState mState;
	sf::Color mIdleColour, mHoverColour, mPushedColour;

};