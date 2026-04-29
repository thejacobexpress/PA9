#pragma once
#include "Fish.hpp"

class Perch : public Fish
{
public:
	Perch(const sf::Vector2f spawnPos) : Fish("water_perch.png", "reel_fish.png", "Perch", 1.0, 1)
	{
		cout << "Perch created!" << endl;
		this->getWaterSprite().setPosition(spawnPos);

		//this->setWaterSprite(this->) //updating water sprite
		//this->setWrangleSprite() //updating wrangle sprite
	};

	~Perch()
	{
		cout << "Perch destroyed!" << endl;
	};

private:

};