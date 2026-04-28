#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using std::string;

class Fish
{
public:
	Fish(string waterTextPath, string wrangleTextPath, string caughtTextPath,
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

	void setCaughtSprite(sf::Sprite newSprite)
	{
		this->caughtSprite = newSprite;
	}

	sf::Sprite& getWaterSprite()
	{
		return this->waterSprite;
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

	int getStrength() {
		return this->strength;
	}

private:
	//Constant data
	string name;
	double size; //measured in lbs (pounds)
	int strength; //Used by the wrangle meter to determine 

	// Texture and sprite of fish in water, wrangling, and caught
	sf::Texture waterText;
	sf::Texture wrangleText;
	sf::Texture caughtText;
	sf::Sprite waterSprite = sf::Sprite(waterText);
	sf::Sprite wrangleSprite = sf::Sprite(wrangleText);
	sf::Sprite caughtSprite = sf::Sprite(caughtText);

	//Runtime data
	bool onRod;
	sf::Vector2f direction; //direction in the lake while moving
};