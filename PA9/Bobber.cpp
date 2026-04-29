#include "Bobber.hpp"

Bobber::Bobber()
{
	bobberText.loadFromFile("bobber1.png");
	bobberSprite = sf::Sprite(bobberText);
	bobberSprite.setOrigin({ bobberSprite.getGlobalBounds().size.x / 2, bobberSprite.getGlobalBounds().size.y / 2 });

	this->canCatch = false;

	this->bobTime = 5000;

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

void Bobber::draw_scene(sf::RenderWindow& window)
{
	window.draw(bobberSprite);
}

void Bobber::timerEnd()
{
	this->canCatch = true;
	std::cout << "Bobber can catch!" << std::endl;
}

//private
//Called from the public function as std::thread cannot take in data members for the lambda
void Bobber::startTimer(int bobTime)
{
	std::cout << "Bobber timer has started. CANNOT CATCH!" << std::endl;
	//Method for timer found via Google AI
	std::thread([this, bobTime]()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(bobTime));
		this->timerEnd();
	}).detach();
}

