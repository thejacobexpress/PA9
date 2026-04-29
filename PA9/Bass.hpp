#pragma once
#include "Fish.hpp"

class Bass : public Fish
{
public:
	Bass(const sf::Vector2f spawnPo) : Fish("water_bass.png", "reel_fish.png", "bass.png", "Bass", 5.0, 3)
	{
		cout << "Bass created!" << endl;
		this->getWaterSprite().setPosition(spawnPos);
	}

	~Bass()
	{
		cout << "Bass destroyed!" << endl;
	};

private:

};