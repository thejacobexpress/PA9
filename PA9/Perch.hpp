#pragma once
#include "Fish.hpp"

class Perch : public Fish
{
public:
	Perch() : Fish("water_perch.png", "reel_fish.png", "Perch", 1.0, 1)
	{
		//this->setWaterSprite() //updating water sprite
		//this->setWrangleSprite() //updating wrangle sprite
	};

private:

};