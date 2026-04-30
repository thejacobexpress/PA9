#include <SFML/Graphics.hpp>
# include <memory>

#include "Bass.hpp"
#include "Catfish.hpp"
#include "Salmon.hpp"
#include "Perch.hpp"

using std::cout;

class Wrangle {
private:
	// Boolean to tell main that this object is done and can be deleted
    bool del = false;
    bool wrangleDone = false, caught = false;
    std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::nano>> startTime;

    float progress = 20;

    sf::Texture barText = sf::Texture();
    sf::Sprite barSprite = sf::Sprite(barText);

    sf::RectangleShape targetBar = sf::RectangleShape({0, 0});
	sf::Vector2f targetBarVelocity = { 0, 0 };
    float gravityAcceleration = 0.02;
    float userAcceleration = 0.1;

	sf::RectangleShape progressBar = sf::RectangleShape({ 0, 0 });
    float progressBarHeight = 420;

    sf::Vector2f fishVelocity = {0, 0};
    float targetPos = -1;

	sf::Texture caughtFishText = sf::Texture();
	sf::Sprite caughtFishSprite = sf::Sprite(caughtFishText);
    
public:
    Wrangle(Fish* fish, sf::RenderWindow& window, float scale);

    void draw_scene(Fish* fish, sf::RenderWindow& window);

	void move_fish(Fish* fish, sf::RenderWindow& window);
    float get_new_loc(Fish* fish, sf::RenderWindow& window);

    bool getCaught();

    bool getDel();

    void updateAccelValues(float newGravityAccel, float newUserAccel);

};