#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Fish
{
public:
	Fish(string waterTextPath, string wrangleTextPath, string caughtTextPath,
		const string newName = "EMPTY_FISH_NAME",
		const double newSize = 0.0,
		const int newStrength = 0);

	virtual ~Fish();

	void wander(sf::RectangleShape& bounds);

	void setWaterSprite(sf::Sprite newSprite)
	{
		this->waterSprite = newSprite;
	}

	void setWrangleSprite(sf::Sprite newSprite)
	{
		this->wrangleSprite = newSprite;
	}

	void setCaughtSprite(sf::Sprite newSprite)
	{
		this->caughtSprite = newSprite;
	}

	void setOnRod(bool newOnRod)
	{
		this->onRod = newOnRod;
	}

	sf::Sprite& getWaterSprite()
	{
		return this->waterSprite;
	}

	sf::Vector2f getWaterPos()
	{
		return this->waterSprite.getPosition();
	}

	sf::Sprite& getWrangleSprite()
	{
		return this->wrangleSprite;
	}

	sf::Sprite& getCaughtSprite()
	{
		return this->caughtSprite;
	}

	sf::Texture& getWaterTexture()
	{
		return this->waterText;
	}

	sf::Texture& getWrangleTexture()
	{
		return this->wrangleText;
	}

	sf::Texture& getCaughtTexture()
	{
		return this->caughtText;
	}

	int getStrength() 
	{
		return this->strength;
	}

	string getName()
	{
		return this->name;
	}

	bool getOnRod()
	{
		return this->onRod;
	}

	void draw_water_sprite(sf::RenderWindow& window);

private:
	//Constant data
	string name;
	double weight; //measured in lbs (pounds)
	int strength; //Used by the wrangle meter to determine 

	// Texture and sprite of fish in water, wrangling, and caught
	sf::Texture waterText;
	sf::Texture wrangleText;
	sf::Texture caughtText;
	sf::Sprite waterSprite = sf::Sprite(waterText);
	sf::Sprite wrangleSprite = sf::Sprite(wrangleText);
	sf::Sprite caughtSprite = sf::Sprite(caughtText);

	//Runtime data
	bool onRod = false;
	sf::Vector2f direction; //direction in the lake while moving
	float waterSpeed;
};