#pragma once
#include "Fish.hpp"

class Catfish : public Fish
{
public:
	Catfish() : Fish("water_catfish.png", "reel_fish.png", "Catfish", 2.0, 2)
	{
		//this->setWaterSprite() //updating water sprite
		//this->setWrangleSprite() //updating wrangle sprite
	};

private:

};