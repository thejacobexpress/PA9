#pragma once
#include "Fish.hpp"

class Catfish : public Fish
{
public:
	Catfish(const sf::Vector2f spawnPos) : Fish("water_catfish.png", "reel_fish.png", "catfish.png", "Catfish", 2.0, 2)
	{
		cout << "Catfish created!" << endl;
		this->getWaterSprite().setPosition(spawnPos);
		//this->setWaterSprite() //updating water sprite
		//this->setWrangleSprite() //updating wrangle sprite
	};

	~Catfish()
	{
		cout << "Catfish created!" << endl;
	};

private:

};