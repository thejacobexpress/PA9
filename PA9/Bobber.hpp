#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>

class Bobber
{
public:
	Bobber();
	~Bobber();

	//Getters
	sf::Texture getBobberText()
	{
		return this->bobberText;
	}
	sf::Sprite getBobberSprite()
	{
		return this->bobberSprite;
	}
	bool getCanCatch()
	{
		return this->canCatch;
	}
	bool getHasFish()
	{
		return this->hasFish;
	}
	bool getTimerRunning()
	{
		return this->timerRunning;
	}

	sf::Vector2f getPosition()
	{
		return this->bobberSprite.getPosition();
	}

	//Setters
	void setPosition(sf::Vector2f newPos);

	void setHasFish(bool newHasFish);

	void draw_scene(sf::RenderWindow& window);

	//Timer
	void startTimer()
	{
		startTimer(this->bobTime);
	}

	void timerEnd();

private:
	sf::Texture bobberText;
	sf::Sprite bobberSprite = sf::Sprite(bobberText);

	//False when timer is not done
	//True otherwise
	bool canCatch;

	//Checks if the 
	bool hasFish;

	//Represents time before bobber can catch fish in milliseconds
	int bobTime;
	bool timerRunning;

	void startTimer(int bobTime);
};