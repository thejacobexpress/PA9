#pragma once
#include "Menu.h" //Includes "Button.h"
#include <optional>

#define BUTTON_WIDTH 200.f
#define BUTTON_HEIGHT 100.f
#define PADDING 25.f

class MainMenu : public Menu
{
public:
	MainMenu(sf::Vector2f windowSize) : Menu(windowSize) //Create buttons
	{
		if (!mStartTexture.loadFromFile("Play.png"))
		{
			//Failed
		}
		if (!mCreditsTexture.loadFromFile("Credits.png"))
		{
			//Failed
		}
		if (!mQuitTexture.loadFromFile("Quit.png"))
		{
			//Failed
		}

		mStartButton.emplace(mStartTexture, sf::Vector2f((windowSize.x / 2.f - (BUTTON_WIDTH / 2.f)), (windowSize.y / 2.f + (BUTTON_HEIGHT / 2.f) - PADDING - BUTTON_HEIGHT)), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
		mCreditsButton.emplace(mCreditsTexture, sf::Vector2f(mStartButton->getPosition().x, (mStartButton->getPosition().y + PADDING + BUTTON_HEIGHT)), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
		mQuitButton.emplace(mQuitTexture, sf::Vector2f(mStartButton->getPosition().x, (mCreditsButton->getPosition().y + PADDING + BUTTON_HEIGHT)), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
	}

	//Update button state with mouse
	void update(const sf::Vector2f& mousePosition) override
	{
		bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		mStartButton->updateButtonState(mousePosition, isPressed);
		mCreditsButton->updateButtonState(mousePosition, isPressed);
		mQuitButton->updateButtonState(mousePosition, isPressed);
	}

	//Draw buttons to screen
	void drawWindow(sf::RenderWindow& window) override
	{
		window.draw(mOverlay);
		
		//Have to use '*' due to the optional found in private for Button; forces button to almost act as pointer
		if (mStartButton)
		{
			window.draw(*mStartButton);
		}
		if (mCreditsButton)
		{
			window.draw(*mCreditsButton);
		}
		if (mQuitButton)
		{
			window.draw(*mQuitButton);
		}
	}

	//Get button state
	bool isStartPushed() const { return mStartButton->getState() == ButtonState::Pushed; }
	bool isCreditsPushed() const { return mCreditsButton->getState() == ButtonState::Pushed; }
	bool isQuitPushed() const { return mQuitButton->getState() == ButtonState::Pushed; }

private:
	sf::Texture mStartTexture, mCreditsTexture, mQuitTexture;
	std::optional<Button> mStartButton, mCreditsButton, mQuitButton;

};