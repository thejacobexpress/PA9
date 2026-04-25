#pragma once
#include "Menu.h" //Includes "Button.h"
#include <optional>

#define BUTTON_WIDTH 60.f
#define BUTTON_HEIGHT 60.f
#define PADDING 20.f

class MerchantMenu : public Menu
{
public:
	MerchantMenu(sf::Vector2f windowSize) : Menu(windowSize) //Create Buttons
	{
		if (!mUpgradeRodSpeedTexture.loadFromFile("RodUpgrade.png"))
		{
			//Failed
		}
		if (!mSellFishTexture.loadFromFile("SellFish.png"))
		{
			//Failed
		}

		mUpgradeRodSpeed.emplace(mUpgradeRodSpeedTexture, sf::Vector2f(windowSize.x / 2.f - 3.f * BUTTON_WIDTH, windowSize.y / 2.f - PADDING - BUTTON_HEIGHT), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
		mSellFish.emplace(mSellFishTexture, sf::Vector2f(windowSize.x / 2.f - 3.f * BUTTON_WIDTH, windowSize.y / 2.f + 2.f * PADDING), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
	}

	//Update button state with mouse
	void update(const sf::Vector2f& mousePosition) override
	{
		mUpgradeRodSpeed->updateButtonState(mousePosition);
		mSellFish->updateButtonState(mousePosition);
	}

	//Draw buttons to the screen
	void drawWindow(sf::RenderWindow& window) override
	{
		window.draw(mOverlay);
		if (mUpgradeRodSpeed)
		{
			window.draw(*mUpgradeRodSpeed);
		}
		if (mSellFish)
		{
			window.draw(*mSellFish);
		}
	}

	//Get the button states
	bool isUpgradeRodSpeedPushed() const { return mUpgradeRodSpeed->getState() == ButtonState::Pushed; } //This is done to remove one extra .cpp file
	bool isSellFishPushed() const { return mSellFish->getState() == ButtonState::Pushed; }

private:
	sf::Texture mUpgradeRodSpeedTexture, mSellFishTexture;
	std::optional<Button> mUpgradeRodSpeed, mSellFish; //This seems to force button to almost act as a pointer

};