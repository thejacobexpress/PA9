#include "Button.h"
#include <string>

void Button::setLocked(bool locked)
{
	if (locked)
	{
		mState = ButtonState::Locked;
		this->setColor(sf::Color(150, 150, 150));
	}
	else
	{
		mState = ButtonState::Idle;
		this->setColor(mIdleColour);
	}
}

bool Button::isLocked(void) const
{
	return mState == ButtonState::Locked;
}

bool Button::contains(const sf::Vector2f& mousePosition)
{
	return this->getGlobalBounds().contains(mousePosition);
}

void Button::updateButtonState(const sf::Vector2f& mousePosition, bool isMousePressed)
{
	if (mState == ButtonState::Locked)
	{
		return;
	}

	mState = ButtonState::Idle; //Default should be idle state

	if (contains(mousePosition)) //If the mouse is in the button
	{
		mState = ButtonState::Hover; //Set the state to hover

		mState = isMousePressed ? ButtonState::Pushed : ButtonState::Hover; //Devided to try and learn Ternarary operators: If mouse is pressed, evalute Right side (pushed), else defautl to Left side (hover)
	}

	switch (mState) //This is to change the colour accordingly; can be use to eventually change sprites
	{
	case ButtonState::Idle:
		setColor(mIdleColour);
		break;
	case ButtonState::Hover:
		setColor(mHoverColour);
		break;
	case ButtonState::Pushed:
		setColor(mPushedColour);
		break;
	}
}

ButtonState Button::getState() const
{
	return mState;
}
