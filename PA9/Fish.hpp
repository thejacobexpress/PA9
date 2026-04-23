#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using std::string;

class Fish
{
public:
	Fish(const string newName = "EMPTY_FISH_NAME", 
		const double newSize = 0.0,
		const int newStrength = 0);

	virtual ~Fish() = 0;

	void wander();

	void setWaterSprite(sf::Sprite newSprite)
	{
		this->waterSprite = newSprite;
	}

	void setWrangleSprite(sf::Sprite newSprite)
	{
		this->wrangleSprite = newSprite;
	}

private:
	//Constant data
	string name;
	double size; //measured in lbs (pounds)
	int strength; //Used by the wrangle meter to determine 
	sf::Sprite waterSprite;
	sf::Sprite wrangleSprite;

	//Runtime data
	bool onRod;
	sf::Vector2f direction; //direction in the lake while moving

	
};