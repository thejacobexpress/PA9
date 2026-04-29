#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


#include "Bass.hpp"
#include "Catfish.hpp"
#include "Perch.hpp"
#include "Salmon.hpp"


class WaterBody
{
public:
	WaterBody();

	//Getters
	int getFishCount()
	{
		return this->fishCount;
	}
	int getMaxFish()
	{
		return this->maxFish;
	}

	sf::RectangleShape& getBounds()
	{
		return this->bounds;
	}

	std::vector<std::unique_ptr<Fish>>& getFishPopulation()
	{
		return this->fishPopulation;
	}

	////////////////////////////

	void incrementFishCount()
	{
		fishCount++;
	}

	void spawnRandomFish();

	void draw_scene(sf::RenderWindow& window);

private:
	int fishCount;
	int maxFish;

	sf::RectangleShape bounds;

	std::vector<std::unique_ptr<Fish>> fishPopulation;

};