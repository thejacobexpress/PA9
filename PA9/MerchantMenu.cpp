#include "MerchantMenu.h"

MerchantMenu::MerchantMenu(sf::Vector2f windowSize) : Menu(windowSize)
{
	if (!mFont.openFromFile("KiwiSoda.ttf"))
	{
		//Failed
	}

	// --- Background: ---
	if (!mTextures.background.loadFromFile("Background.png"))
	{
		//Failed
	}

	// --- Upgrades: ---
	if (!mTextures.rodSpeed.loadFromFile("RodUpgrade.png"))
	{
		//Failed
	}
	if (!mTextures.sell.loadFromFile("SellFish.png"))
	{
		//Failed
	}
	if (!mTextures.timer.loadFromFile("UpgradeTimer.png"))
	{
		//Failed
	}

	//For padding, each button relies off of button above it; first button is "master button"
	mUpgradeRodSpeed.emplace(mTextures.rodSpeed, sf::Vector2f(windowSize.x / 2.f - 8.f * UPGRADE_WIDTH, windowSize.y / 2.f - PADDING - UPGRADE_HEIGHT), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
	mUpgradeTimer.emplace(mTextures.timer, sf::Vector2f(mUpgradeRodSpeed->getPosition().x, mUpgradeRodSpeed->getPosition().y + UPGRADE_HEIGHT + PADDING * 2.f), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
	mSellFish.emplace(mTextures.sell, sf::Vector2f(mUpgradeRodSpeed->getPosition().x, mUpgradeTimer->getPosition().y + UPGRADE_HEIGHT + PADDING * 2.f), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));

	// --- Players: ----
	if (!mTextures.player1.loadFromFile("Player1.png"))
	{
		//Failed
	}
	if (!mTextures.player2.loadFromFile("Player2.png"))
	{
		//Failed
	}
	if (!mTextures.player3.loadFromFile("Player3.png"))
	{
		//Failed
	}
	//Master button
	mPlayer1.emplace(mTextures.player1, sf::Vector2f(windowSize.x - 6.f * PLAYER_WIDTH, windowSize.y - PLAYER_HEIGHT - 2.f * PADDING), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
	mPlayer2.emplace(mTextures.player2, sf::Vector2f(mPlayer1->getPosition().x + PLAYER_WIDTH + 2.f * PADDING, mPlayer1->getPosition().y), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
	mPlayer3.emplace(mTextures.player3, sf::Vector2f(mPlayer2->getPosition().x + PLAYER_WIDTH + 2.f * PADDING, mPlayer1->getPosition().y), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));

	mPlayer1->setLocked(true);
	mPlayer2->setLocked(true);
	mPlayer3->setLocked(true);


	// --- Rods: ---
	if (!mTextures.rod1.loadFromFile("Rod1.png"))
	{
		//Failed
	}
	if (!mTextures.rod2.loadFromFile("Rod2.png"))
	{
		//Failed
	}
	if (!mTextures.rod3.loadFromFile("Rod3.png"))
	{
		//Failed
	}
	//Master button IS mPlayer1
	mRod1.emplace(mTextures.rod1, sf::Vector2f(mPlayer1->getPosition().x, mPlayer1->getPosition().y - ROD_SIZE - PADDING), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
	mRod2.emplace(mTextures.rod2, sf::Vector2f(mRod1->getPosition().x + ROD_SIZE + 2.f * PADDING, mRod1->getPosition().y), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));
	mRod3.emplace(mTextures.rod3, sf::Vector2f(mRod2->getPosition().x + ROD_SIZE + 2.f * PADDING, mRod2->getPosition().y), sf::Color::White, sf::Color(150, 150, 150), sf::Color(100, 100, 100));

	mRod1->setLocked(true);
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

	std::string moneyStr = std::to_string(money), rodStr = std::to_string(rodLevel), timeStr = std::to_string(timeLevel);

	mRodUpgrade.setPosition(sf::Vector2f(window.getSize().x / 2.f - 8.f * UPGRADE_WIDTH + 3.5f * PADDING, window.getSize().y / 2.f - PADDING - UPGRADE_HEIGHT + 8.f));
	mTimerUpgrade.setPosition(sf::Vector2f(mRodUpgrade.getPosition().x, mRodUpgrade.getPosition().y + UPGRADE_HEIGHT + 2.f * PADDING));
	mMoney.setPosition(sf::Vector2f(mTimerUpgrade.getPosition().x, mTimerUpgrade.getPosition().y + UPGRADE_HEIGHT + 2.f * PADDING));
	mName.setPosition(sf::Vector2f(window.getSize().x / 2.f - 10.f * PADDING, 2.f * PADDING));

	mRodUpgrade.setString("Rod Level: " + rodStr);
	mTimerUpgrade.setString("Timer-Reduction Level: " + timeStr);
	mMoney.setString("Money: " + moneyStr);

	mName.setCharacterSize(100);
	mName.setFillColor(sf::Color(239, 222, 205));
	mName.setOutlineThickness(5);
	mName.setOutlineColor(sf::Color(100, 65, 23)); //This colour code is "Pullman Brown" :)

	window.draw(mRodUpgrade);
	window.draw(mTimerUpgrade);
	window.draw(mMoney);
	window.draw(mName);
}

void MerchantMenu::handleButtonClicks(const sf::Vector2f& clickPosition, int& money, int& rodLevel, int& timerLevel)
{
	if (mUpgradeRodSpeed->contains(clickPosition) && rodLevel < 5)
	{
		++rodLevel;
	}
	else if (mUpgradeTimer->contains(clickPosition) && timerLevel < 5)
	{
		++timerLevel;
	}
	else if (mSellFish->contains(clickPosition))
	{
		money += money + 1 * 10;
	}
	else if (mPlayer1->contains(clickPosition))
	{
		if (mPlayer1->isLocked() && money > PLAYER_COSMETIC_COST)
		{
			mPlayer1->setLocked(false);
			money = money - PLAYER_COSMETIC_COST;
			std::cout << "Bought" << std::endl;
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
	}
	else if (mPlayer3->contains(clickPosition))
	{
		if (mPlayer3->isLocked() && money > PLAYER_COSMETIC_COST)
		{
			mPlayer3->setLocked(false);
			money = money - PLAYER_COSMETIC_COST;
			std::cout << "Bought" << std::endl;
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
	}
	else if (mRod2->contains(clickPosition))
	{
		if (mRod2->isLocked() && money > ROD_COSMETIC_COST)
		{
			mRod2->setLocked(false);
			money = money - ROD_COSMETIC_COST;
			std::cout << "Bought" << std::endl;
		}
	}
	else if (mRod3->contains(clickPosition))
	{
		if (mRod3->isLocked() && money > ROD_COSMETIC_COST)
		{
			mRod3->setLocked(false);
			money = money - ROD_COSMETIC_COST;
			std::cout << "Bought" << std::endl;
		}
	}
}

