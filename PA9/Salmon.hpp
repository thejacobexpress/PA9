#pragma once
#include "Fish.hpp"

class Salmon : public Fish
{
public:
	Salmon() : Fish("water_salmon.png", "reel_fish.png", "bass.png", "Salmon", 10.0, 4)
	{
		//this->setWaterSprite() //updating water sprite
		//this->setWrangleSprite() //updating wrangle sprite
	};

private:

};