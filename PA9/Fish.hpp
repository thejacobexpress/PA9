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
	Fish(string waterTextPath, string wrangleTextPath,
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

	sf::Texture& getWaterTexture()
	{
		return this->waterText;
	}

	sf::Texture& getWrangleTexture()
	{
		return this->wrangleText;
	}

	int getStrength() 
	{
		return this->strength;
	}

	void draw_water_sprite(sf::RenderWindow& window);

private:
	//Constant data
	string name;
	double size; //measured in lbs (pounds)
	int strength; //Used by the wrangle meter to determine 

	sf::Texture waterText;
	sf::Texture wrangleText;
	sf::Sprite waterSprite = sf::Sprite(waterText);
	sf::Sprite wrangleSprite = sf::Sprite(wrangleText);

	//Runtime data
	bool onRod;
	sf::Vector2f direction; //direction in the lake while moving
};