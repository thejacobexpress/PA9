#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using std::string;

class Fish
{
public:
	Fish(string waterTextPath, string wrangleTextPath,
		const string newName = "EMPTY_FISH_NAME",
		const double newSize = 0.0,
		const int newStrength = 0);

	virtual ~Fish();

	void wander();

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

	sf::Sprite& getWrangleSprite()
	{
		return this->wrangleSprite;
	}

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