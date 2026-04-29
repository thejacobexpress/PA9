#include "WaterBody.hpp"

WaterBody::WaterBody()
{
	this->maxFish = 100;
	this->fishCount = 0;

	this->bounds = sf::RectangleShape({ 1200, 500 });
	this->bounds.setPosition({ 40, 40 });
}

void WaterBody::spawnRandomFish()
{
	int fishChosen = std::rand() % 100 + 1;

	sf::Vector2f spawnPos;
	float x = static_cast<float>(rand() % 1000) + 50;
	float y = static_cast<float>(rand() % 400) + 50;
	spawnPos.x = x;
	spawnPos.y = y;

	//Perch has 50% chance
	if (fishChosen >= 1 && fishChosen < 50)
	{
		this->fishPopulation.emplace_back(std::make_unique<Perch>(spawnPos));
	}
	//Catfish has 28%
	else if (fishChosen >= 50 && fishChosen < 78)
	{
		this->fishPopulation.emplace_back(std::make_unique<Catfish>(spawnPos));
	}
	//Bass has 15%
	else if (fishChosen >= 78 && fishChosen < 93)
	{
		this->fishPopulation.emplace_back(std::make_unique<Bass>(spawnPos));
	}
	//Salmon has 7%
	else
	{
		this->fishPopulation.emplace_back(std::make_unique<Salmon>(spawnPos));
	}
}


void WaterBody::draw_scene(sf::RenderWindow& window)
{
	window.draw(this->bounds);
}

