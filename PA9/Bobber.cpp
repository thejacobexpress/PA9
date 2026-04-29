#include "Bobber.hpp"

Bobber::Bobber()
{
	bobberText.loadFromFile("bobber1.png");
	bobberSprite = sf::Sprite(bobberText);
	bobberSprite.setOrigin({ bobberSprite.getGlobalBounds().size.x / 2, bobberSprite.getGlobalBounds().size.y / 2 });

	this->canCatch = false;
	this->hasFish = false;

	this->bobTime = 5000;
	this->timerRunning = false;

	//DEBUGGING
	std::cout << "Bobber has been created" << std::endl;
}

Bobber::~Bobber()
{
	//DEBUGGING
	std::cout << "Bobber has been destroyed" << std::endl;
}

void Bobber::setPosition(sf::Vector2f newPos)
{
	this->bobberSprite.setPosition(newPos);
}

void Bobber::setHasFish(bool newHasFish)
{
	this->hasFish = newHasFish;
}

void Bobber::draw_scene(sf::RenderWindow& window)
{
	window.draw(bobberSprite);
}

//bool Bobber::hasFish(WaterBody& water)
//{
//	for (auto& fishPtr : water.getFishPopulation())
//	{
//		if (this->getBobberSprite().getGlobalBounds().contains(fishPtr->getWaterPos()))
//		{
//			return true;
//		}
//	}
//	return false;
//}

void Bobber::timerEnd()
{
	this->canCatch = true;
	this->timerRunning = false;
	this->bobberSprite.setColor(sf::Color(255, 255, 255, 255)); /*make bobber non-transparent*/
	std::cout << "Bobber can catch!" << std::endl;
}

//private
//Called from the public function as std::thread cannot take in data members for the lambda
void Bobber::startTimer(int bobTime)
{
	std::cout << "Bobber timer has started. CANNOT CATCH!" << std::endl;
	this->timerRunning = true;
	this->canCatch = false;
	this->bobberSprite.setColor(sf::Color(255, 255, 255, 128)); /*make bobber semi transparent*/
	//Method for timer found via Google AI
	std::thread([this, bobTime]()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(bobTime));
		this->timerEnd();
	}).detach();
}

