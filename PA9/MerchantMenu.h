#pragma once
#include "Menu.h" //Includes "Button.h"
#include "Bobber.hpp"
#include <optional>
#include <string>
#include <vector>
#include <iostream>

#define PADDING 20.f

#define UPGRADE_WIDTH 60.f
#define UPGRADE_HEIGHT 60.f

#define PLAYER_WIDTH 100.f
#define PLAYER_HEIGHT 200.f

#define ROD_SIZE 100.f

#define PLAYER_COSMETIC_COST 1000
#define ROD_COSMETIC_COST 1000
#define ROD_UPGRADE_MAX_LEVEL 5
#define TIMER_UPGRADE_MAX_LEVEL 5

using std::cout;
using std::endl;

class MerchantMenu : public Menu
{
public:
	MerchantMenu(sf::Vector2f windowSize); //Create Buttons

	//Update button state with mouse
	void update(const sf::Vector2f& mousePosition) override;

	//Draw buttons to the screen
	void drawWindow(sf::RenderWindow& window) override;

	void drawWindow(sf::RenderWindow& window, int money, int rodLevel, int timeLevel);

	//Buying and selling
	void handleButtonClicks(const sf::Vector2f& clickPosition, int& money, int& fishMoneyToSell, int& rodLevel, int& timerLevel, Bobber& bobber);
	

private:
	sf::Font mFont;
	struct Textures
	{
		sf::Texture background, rodSpeed, timer, sell, player1, player2, player3, rod1, rod2, rod3;
	} mTextures;
	
	std::optional<Button> mUpgradeRodSpeed, mUpgradeTimer, mSellFish, mPlayer1, mPlayer2, mPlayer3, mRod1, mRod2, mRod3; //Makes buttons almsot act like pointers.

	std::vector<Button*> mAllButtons;

	int mRodSpeedUpgradeCost, mTimerUpgradeCost;

};