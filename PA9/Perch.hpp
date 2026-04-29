#pragma once
#include "Fish.hpp"

class Perch : public Fish
{
public:
	Perch(const sf::Vector2f spawnPos) : Fish("water_perch.png", "reel_perch.png", "perch.png", "Perch", 1.0, 1)
	{
		cout << "Perch created!" << endl;
		this->getWaterSprite().setPosition(spawnPos);
	};

	~Perch()
	{
		cout << "Perch destroyed!" << endl;
	};

private:

};