#include "Fish.hpp"

Fish::Fish(string waterTextPath, string wrangleTextPath, const string newName,
	const double newSize, const int newStrength)
{
	this->name = newName;
	this->size = newSize;
	this->strength = newStrength;
	this->onRod = false;
	this->direction = {static_cast<float>((rand() % 200) - 100), 
		static_cast<float>((rand() % 200) - 100) };
	this->waterText.loadFromFile(waterTextPath);
	this->wrangleText.loadFromFile(wrangleTextPath);
	this->setWaterSprite(sf::Sprite(waterText));
	this->setWrangleSprite(sf::Sprite(wrangleText));
}

Fish::~Fish() {

}

void Fish::wander(sf::RectangleShape& bounds)
{
	this->direction = this->direction.normalized();
	this->getWaterSprite().move(this->direction * .05f);

	if (!bounds.getGlobalBounds().contains(this->getWaterSprite().getPosition()))
	{
		this->direction *= -1.0f;
	}
}

void Fish::draw_water_sprite(sf::RenderWindow& window)
{
	window.draw(this->waterSprite);
}
