#include "Fish.hpp"

Fish::Fish(string waterTextPath, string wrangleTextPath, string caughtTextPath, const string newName,
	const double newWeight, const int newStrength)
{
	this->name = newName;
	this->weight = newWeight;
	this->strength = newStrength;
	this->onRod = false;
	this->waterSpeed = 0.8f;
	this->direction = {0,1};
	this->waterText.loadFromFile(waterTextPath);
	this->wrangleText.loadFromFile(wrangleTextPath);
	this->caughtText.loadFromFile(caughtTextPath);
	this->setWaterSprite(sf::Sprite(waterText));
	this->getWaterSprite().setOrigin({ 15,15 });
	this->setWrangleSprite(sf::Sprite(wrangleText));
	this->setCaughtSprite(sf::Sprite(caughtText));
}

Fish::~Fish() {

}

void Fish::wander(sf::RectangleShape& bounds)
{
	//Normalize direction & move
	this->direction = this->direction.normalized();
	this->waterSprite.move(this->direction * this->waterSpeed);

	//Rotating the fish sprite
	float angleRad = std::atan2(direction.y, direction.x);
	float angleDef = angleRad * 180.f / 3.14159f;
	this->waterSprite.setRotation(sf::degrees(angleDef - 90.f));
	
	if (rand() % 60 < 1)
	{
		//randomize direction randomly
		this->direction = { this->direction.x + static_cast<float>((rand() % 200) - 100) / 100.0f, this->direction.y + static_cast<float>((rand() % 200) - 100) / 100.0f };
	}

	if (!bounds.getGlobalBounds().contains(this->getWaterSprite().getPosition()))
	{
		this->direction *= -1.0f;
	}
}

void Fish::draw_water_sprite(sf::RenderWindow& window)
{
	window.draw(this->waterSprite);
}
