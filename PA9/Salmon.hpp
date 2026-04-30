#pragma once
#include "Fish.hpp"

class Salmon : public Fish
{
public:
	Salmon(const sf::Vector2f spawnPos) : Fish("water_salmon.png", "reel_fish.png", "salmon.png", "Salmon", 10.0, 4, 100)
	{
		cout << "Salmon created!" << endl;
		this->getWaterSprite().setPosition(spawnPos);
	};

	~Salmon()
	{
		cout << "Salmon destroyed!" << endl;
	};

private:

};