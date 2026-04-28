#include "Fish.hpp"

Fish::Fish(string waterTextPath, string wrangleTextPath, string caughtTextPath, const string newName,
	const double newSize, const int newStrength)
{
	this->name = newName;
	this->size = newSize;
	this->strength = newStrength;
	this->onRod = false;
	this->direction = {};
	this->waterText.loadFromFile(waterTextPath);
	this->wrangleText.loadFromFile(wrangleTextPath);
	this->caughtText.loadFromFile(caughtTextPath);
	this->setWaterSprite(sf::Sprite(waterText));
	this->setWrangleSprite(sf::Sprite(wrangleText));
	this->setCaughtSprite(sf::Sprite(caughtText));
}

Fish::~Fish() {

}

void Fish::wander()
{

}
