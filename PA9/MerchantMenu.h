#pragma once
#include "Menu.h" //Includes "Button.h"
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

#define PLAYER_COSMETIC_COST 100
#define ROD_COSMETIC_COST 100

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
	void handleButtonClicks(const sf::Vector2f& clickPosition, int& money, int& rodLevel, int& timerLevel);

	////Get the button states; Holy bloat...
	//bool isUpgradeRodSpeedPushed() const { return mUpgradeRodSpeed->getState() == ButtonState::Pushed; }
	//bool isSellFishPushed() const { return mSellFish->getState() == ButtonState::Pushed; }
	//bool isUpgradeTimerPushed() const { return mUpgradeTimer->getState() == ButtonState::Pushed; }
	//bool isPlayer1Pushed() const { return mPlayer1->getState() == ButtonState::Pushed; }
	//bool isPlayer2Pushed() const { return mPlayer2->getState() == ButtonState::Pushed; }
	//bool isPlayer3Pushed() const { return mPlayer3->getState() == ButtonState::Pushed; }
	//bool isRod1Pushed() const { return mRod1->getState() == ButtonState::Pushed; }
	//bool isRod2Pushed() const { return mRod2->getState() == ButtonState::Pushed; }
	//bool isRod3Pushed() const { return mRod3->getState() == ButtonState::Pushed; }

	////Setters and Getters
	//void setPlayer1State(const bool state) { mPlayer1->setLocked(state); }
	//void setPlayer2State(const bool state) { mPlayer2->setLocked(state); }
	//void setPlayer3State(const bool state) { mPlayer3->setLocked(state); }
	//void setRod1State(const bool state) { mRod1->setLocked(state); }
	//void setRod2State(const bool state) { mRod2->setLocked(state); }
	//void setRod3State(const bool state) { mRod3->setLocked(state); }

	//bool getPlayer1State(void) const { return mPlayer1->getLocked() == ButtonState::Locked; }
	//bool getPlayer2State(void) const { return mPlayer2->getLocked() == ButtonState::Locked; }
	//bool getPlayer3State(void) const { return mPlayer3->getLocked() == ButtonState::Locked; }
	//bool getRod1State(void) const { return mRod1->getLocked() == ButtonState::Locked; }
	//bool getRod2State(void) const { return mRod2->getLocked() == ButtonState::Locked; }
	//bool getRod3State(void) const { return mRod3->getLocked() == ButtonState::Locked; }

	////Have to do this to allow only one click instead of holding
	//std::optional<Button> getUpgradeRodSpeed(void) const { return mUpgradeRodSpeed; }
	//std::optional<Button> getUpgradeTimer(void) const { return mUpgradeTimer; }
	//std::optional<Button> getSellFish(void) const { return mSellFish; }
	//std::optional<Button> getPlayer1(void) const { return mPlayer1; }
	//std::optional<Button> getPlayer2(void) const { return mPlayer2; }
	//std::optional<Button> getPlayer3(void) const { return mPlayer3; }
	//std::optional<Button> getRod1(void) const { return mRod1; }
	//std::optional<Button> getRod2(void) const { return mRod2; }
	//std::optional<Button> getRod3(void) const { return mRod3; }
	

private:
	sf::Font mFont;
	struct Textures
	{
		sf::Texture background, rodSpeed, timer, sell, player1, player2, player3, rod1, rod2, rod3;
	} mTextures;
	
	std::optional<Button> mUpgradeRodSpeed, mUpgradeTimer, mSellFish, mPlayer1, mPlayer2, mPlayer3, mRod1, mRod2, mRod3; //Makes buttons almsot act like pointers.

	std::vector<Button*> mAllButtons;

};