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
	int fishChosen = std::rand() % 4 + 1;

	sf::Vector2f spawnPos;
	float x = static_cast<float>(rand() % 1000) + 50;
	float y = static_cast<float>(rand() % 400) + 50;
	spawnPos.x = x;
	spawnPos.y = y;

	switch (fishChosen)
	{
	case 1:
	{
		this->fishPopulation.emplace_back(std::make_unique<Perch>(spawnPos));
		break;
	}
	case 2:
	{
		this->fishPopulation.emplace_back(std::make_unique<Catfish>(spawnPos));
		break;
	}
	case 3:
	{
		this->fishPopulation.emplace_back(std::make_unique<Bass>(spawnPos));
		break;
	}
	case 4:
	{
		this->fishPopulation.emplace_back(std::make_unique<Salmon>(spawnPos));
		break;
	}
	}
}


void WaterBody::draw_scene(sf::RenderWindow& window)
{
	window.draw(this->bounds);
}

