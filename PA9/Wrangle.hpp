#include <SFML/Graphics.hpp>

#include "Bass.hpp"
#include "Catfish.hpp"
#include "Salmon.hpp"
#include "Perch.hpp"

using std::cout;

class Wrangle {
private:
    sf::Texture barText = sf::Texture();
    sf::Sprite barSprite = sf::Sprite(barText);

    sf::Vector2f fishVelocity = {0, 0};
    float fishAcceleration = 0.01;
public:
    Wrangle(Fish& fish, sf::RenderWindow& window, float scale);

    void draw_scene(Fish& fish, sf::RenderWindow& window);

    float get_new_loc(Fish& fish, sf::RenderWindow& window);
};