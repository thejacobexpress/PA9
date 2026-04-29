#pragma once
#include "Fish.hpp"

class Salmon : public Fish
{
public:
	Salmon(const sf::Vector2f spawnPos) : Fish("water_salmon.png", "reel_fish.png", "Salmon", 10.0, 4)
	{
		cout << "Salmon created!" << endl;
		this->getWaterSprite().setPosition(spawnPos);
		//this->setWaterSprite() //updating water sprite
		//this->setWrangleSprite() //updating wrangle sprite
	};

	~Salmon()
	{
		cout << "Salmon destroyed!" << endl;
	};

private:

};