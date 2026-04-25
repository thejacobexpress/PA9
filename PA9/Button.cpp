#include "Button.h"

void Button::updateButtonState(const sf::Vector2f& mousePosition)
{
	mState = ButtonState::Idle; //Default should be idle state

	if (this->getGlobalBounds().contains(mousePosition)) //If the mouse is in the gloabl bounds of the button object
	{
		mState = ButtonState::Hover; //Set the state to hover

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) //If the user presses the left-mouse button, set the state to pushed
		{
			mState = ButtonState::Pushed;
		}
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
