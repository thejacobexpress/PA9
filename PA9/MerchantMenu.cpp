#include "MerchantMenu.h"

MerchantMenu::MerchantMenu(sf::Vector2f windowSize) : Menu(windowSize)
{
	mRodSpeedUpgradeCost = 100;
	mTimerUpgradeCost = 100;

	if (!mFont.openFromFile("KiwiSoda.ttf"))
	{
		//Failed
		cout << "Font failed to load" << endl;
	}

	// --- Background: ---
	if (!mTextures.background.loadFromFile("BackgroundMerchant.png"))
	{
		//Failed
		cout << "Background for merchant failed to load" << endl;
	}

	// --- Upgrades: ---
	if (!mTextures.rodSpeed.loadFromFile("RodUpgrade.png"))
	{
		//Failed
		cout << "Rod upgrade failed to load" << endl;
	}
	if (!mTextures.sell.loadFromFile("SellFish.png"))
	{
		//Failed
		cout << "Sell fish failed to load" << endl;
	}
	if (!mTextures.timer.loadFromFile("UpgradeTimer.png"))
	{
		//Failed
		cout << "Timer upgrade failed to load" << endl;
	}

	//For padding, each button relies off of button above it; first button is "master button"
	mUpgradeRodSpeed.emplace(mTextures.rodSpeed, sf::Vector2f(windowSize.x / 2.f - 8.f * UPGRADE_WIDTH, windowSize.y / 2.f - PADDING - UPGRADE_HEIGHT), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
	mUpgradeTimer.emplace(mTextures.timer, sf::Vector2f(mUpgradeRodSpeed->getPosition().x, mUpgradeRodSpeed->getPosition().y + UPGRADE_HEIGHT + PADDING * 2.f), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
	mSellFish.emplace(mTextures.sell, sf::Vector2f(mUpgradeRodSpeed->getPosition().x, mUpgradeTimer->getPosition().y + UPGRADE_HEIGHT + PADDING * 2.f), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));

	// --- Players: ----
	if (!mTextures.player1.loadFromFile("Player1.png"))
	{
		//Failed
		cout << "Player 1 failed to load" << endl;
	}
	if (!mTextures.player2.loadFromFile("Player2.png"))
	{
		//Failed
		cout << "Player 2 failed to load" << endl;
	}
	if (!mTextures.player3.loadFromFile("Player3.png"))
	{
		//Failed
		cout << "Player 3 failed to load" << endl;
	}
	//Master button
	mPlayer1.emplace(mTextures.player1, sf::Vector2f(windowSize.x - 6.f * PLAYER_WIDTH, windowSize.y - PLAYER_HEIGHT - 2.f * PADDING), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
	mPlayer2.emplace(mTextures.player2, sf::Vector2f(mPlayer1->getPosition().x + PLAYER_WIDTH + 2.f * PADDING, mPlayer1->getPosition().y), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
	mPlayer3.emplace(mTextures.player3, sf::Vector2f(mPlayer2->getPosition().x + PLAYER_WIDTH + 2.f * PADDING, mPlayer1->getPosition().y), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));

	mPlayer1->setLocked(false); //Because this is defualt
	mPlayer2->setLocked(true);
	mPlayer3->setLocked(true);


	// --- Rods: ---
	if (!mTextures.rod1.loadFromFile("MerchantBobber1.png"))
	{
		//Failed
		cout << "Rod 1 failed to load" << endl;
	}
	if (!mTextures.rod2.loadFromFile("MerchantBobber2.png"))
	{
		//Failed
		cout << "Rod 2 failed to load" << endl;
	}
	if (!mTextures.rod3.loadFromFile("MerchantBobber3.png"))
	{
		//Failed
		cout << "Rod 3 failed to load" << endl;
	}
	//Master button IS mPlayer1
	mRod1.emplace(mTextures.rod1, sf::Vector2f(mPlayer1->getPosition().x, mPlayer1->getPosition().y - ROD_SIZE - PADDING), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
	mRod2.emplace(mTextures.rod2, sf::Vector2f(mRod1->getPosition().x + ROD_SIZE + 2.f * PADDING, mRod1->getPosition().y), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
	mRod3.emplace(mTextures.rod3, sf::Vector2f(mRod2->getPosition().x + ROD_SIZE + 2.f * PADDING, mRod2->getPosition().y), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));

	mRod1->setLocked(false); //Becuase this is defualt
	mRod2->setLocked(true);
	mRod3->setLocked(true);

	mAllButtons = { &mUpgradeRodSpeed.value(), &mUpgradeTimer.value(), &mSellFish.value(), &mPlayer1.value(), &mPlayer2.value(), &mPlayer3.value(), &mRod1.value(), &mRod2.value(), &mRod3.value()}; //.value() is required due to optional

}

void MerchantMenu::update(const sf::Vector2f& mousePosition)
{
	bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	for (Button* button : mAllButtons) //Gemini helped with de-bloading/refactoring. Prompt: "Refactor this code, please :)"
	{
		button->updateButtonState(mousePosition, isPressed);
	}
}

void MerchantMenu::drawWindow(sf::RenderWindow& window)
{
	sf::Sprite background(mTextures.background);
	background.setPosition(sf::Vector2f(PADDING, PADDING));

	window.draw(mOverlay);
	window.draw(background);

	for (Button* button : mAllButtons)
	{
		window.draw(*button);
	}
}

void MerchantMenu::drawWindow(sf::RenderWindow& window, int money, int rodLevel, int timeLevel)
{
	sf::Text mRodUpgrade(mFont, "Rod Level: "), mTimerUpgrade(mFont, "Timer-Reduction Level: "), mMoney(mFont, "Money: "), mName(mFont, "Merchant"); //No defualt constructor for sf::Text
	sf::Text mRodCost(mFont, ""), mTimerCost(mFont, "");

	std::string moneyStr = std::to_string(money), rodStr = std::to_string(rodLevel), timeStr = std::to_string(timeLevel);
	std::string rodCostStr = std::to_string(mRodSpeedUpgradeCost), timerCostStr = std::to_string(mTimerUpgradeCost);

	mRodUpgrade.setPosition(sf::Vector2f(window.getSize().x / 2.f - 8.f * UPGRADE_WIDTH + 3.5f * PADDING, window.getSize().y / 2.f - PADDING - UPGRADE_HEIGHT + 8.f));
	mTimerUpgrade.setPosition(sf::Vector2f(mRodUpgrade.getPosition().x, mRodUpgrade.getPosition().y + UPGRADE_HEIGHT + 2.f * PADDING));
	mMoney.setPosition(sf::Vector2f(mTimerUpgrade.getPosition().x, mTimerUpgrade.getPosition().y + UPGRADE_HEIGHT + 2.f * PADDING));
	mRodUpgrade.setString("Rod Level: " + rodStr);
	mTimerUpgrade.setString("Timer-Reduction Level: " + timeStr);
	mMoney.setString("Money: " + moneyStr);

	mRodCost.setPosition(sf::Vector2f(window.getSize().x / 2.f - 8.f * UPGRADE_WIDTH + PADDING * 0.5f, window.getSize().y / 2.f - PADDING - UPGRADE_HEIGHT + 8.f));
	mTimerCost.setPosition(sf::Vector2f(mRodCost.getPosition().x, mRodCost.getPosition().y + UPGRADE_HEIGHT + 2.f * PADDING));
	if (rodLevel != ROD_UPGRADE_MAX_LEVEL)
	{
		mRodCost.setString(rodCostStr);
	}
	else
	{
		mRodCost.setString("Max");
	}
	if (timeLevel != TIMER_UPGRADE_MAX_LEVEL)
	{
		mTimerCost.setString(timerCostStr);
	}
	else
	{
		mTimerCost.setString("Max");
	}
	mRodCost.setFillColor(sf::Color(27, 27, 27, 200));
	mTimerCost.setFillColor(mRodCost.getFillColor());

	mName.setPosition(sf::Vector2f(window.getSize().x / 2.f - 10.f * PADDING, 2.f * PADDING));
	mName.setCharacterSize(100);
	mName.setFillColor(sf::Color(239, 222, 205));
	mName.setOutlineThickness(5);
	mName.setOutlineColor(sf::Color(100, 65, 23)); //This colour code is "Pullman Brown" :)

	std::string cosmeticCostStr = std::to_string(PLAYER_COSMETIC_COST);
	sf::Text mCosmeticCost(mFont, "Cosmetic Cost: " + cosmeticCostStr);
	mCosmeticCost.setPosition(sf::Vector2f(window.getSize().x - 6.f * PLAYER_WIDTH, window.getSize().y - PLAYER_HEIGHT - ROD_SIZE - 6.f * PADDING));

	window.draw(mRodUpgrade);
	window.draw(mTimerUpgrade);
	window.draw(mMoney);
	window.draw(mName);
	window.draw(mRodCost);
	window.draw(mTimerCost);
	window.draw(mCosmeticCost);
}

void MerchantMenu::handleButtonClicks(const sf::Vector2f& clickPosition, int& money, int& fishMoneyToSell, int& rodLevel, int& timerLevel, Bobber& bobber)
{
	if (mUpgradeRodSpeed->contains(clickPosition) && rodLevel < ROD_UPGRADE_MAX_LEVEL && money > mRodSpeedUpgradeCost)
	{
		++rodLevel;
		money -= mRodSpeedUpgradeCost;
		mRodSpeedUpgradeCost = mRodSpeedUpgradeCost * UPGRADE_MULTIPLER;
	}
	else if (mUpgradeTimer->contains(clickPosition) && timerLevel < TIMER_UPGRADE_MAX_LEVEL && money > mTimerUpgradeCost)
	{
		++timerLevel;
		money -= mTimerUpgradeCost;
		bobber.updateBobberTimer(timerLevel);
		mTimerUpgradeCost = mTimerUpgradeCost * UPGRADE_MULTIPLER;
	}
	else if (mSellFish->contains(clickPosition))
	{
		money += fishMoneyToSell;
		fishMoneyToSell = 0;
	}
	else if (mPlayer1->contains(clickPosition))
	{
		if (mPlayer1->isLocked() && money > PLAYER_COSMETIC_COST)
		{
			mPlayer1->setLocked(false);
			money = money - PLAYER_COSMETIC_COST;
			std::cout << "Bought" << std::endl;
		}
		if (!mPlayer1->isLocked())
		{
			//Change player
		}
	}
	else if (mPlayer2->contains(clickPosition))
	{
		if (mPlayer2->isLocked() && money > PLAYER_COSMETIC_COST)
		{
			mPlayer2->setLocked(false);
			money = money - PLAYER_COSMETIC_COST;
			std::cout << "Bought" << std::endl;
		}
		if (!mPlayer2->isLocked())
		{
			//Change player
		}
	}
	else if (mPlayer3->contains(clickPosition))
	{
		if (mPlayer3->isLocked() && money > PLAYER_COSMETIC_COST)
		{
			mPlayer3->setLocked(false);
			money = money - PLAYER_COSMETIC_COST;
			std::cout << "Bought" << std::endl;
		}
		if (!mPlayer3->isLocked())
		{
			//Change player
		}
	}
	else if (mRod1->contains(clickPosition))
	{
		if (mRod1->isLocked() && money > ROD_COSMETIC_COST)
		{
			mRod1->setLocked(false);
			money = money - ROD_COSMETIC_COST;
			std::cout << "Bought" << std::endl;
		}
		if (!mRod1->isLocked())
		{
			bobber.setBobber("bobber1.png");
		}
	}
	else if (mRod2->contains(clickPosition))
	{
		if (mRod2->isLocked() && money > ROD_COSMETIC_COST)
		{
			mRod2->setLocked(false);
			money = money - ROD_COSMETIC_COST;
			std::cout << "Bought" << std::endl;
		}
		if (!mRod2->isLocked())
		{
			bobber.setBobber("bobber2.png");
		}
	}
	else if (mRod3->contains(clickPosition))
	{
		if (mRod3->isLocked() && money > ROD_COSMETIC_COST)
		{
			mRod3->setLocked(false);
			money = money - ROD_COSMETIC_COST;
			std::cout << "Bought" << std::endl;
			bobber.setBobber("bobber3.png");
		}
		if (!mRod3->isLocked())
		{
			bobber.setBobber("bobber3.png");
		}
	}
}

