#include <SFML/Graphics.hpp>
#include "Bass.hpp"
#include "Wrangle.hpp"
#include "Bobber.hpp"
#include "WaterBody.hpp"

int main()
{
    std::srand(std::time(NULL));

    float scale = 1;

    //Player variables
    float currency = 0.0;
    
    //Window
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "SFML (Savage Fish Mayhem Live)");

    //Bass bass;
	//Wrangle wrangle(bass, window, scale);

    //Water
    WaterBody water;

    //Background & foreground texture
    sf::Texture bgWaterText;
    sf::Texture bgBeachText;
    sf::Texture bgObjectsText;
    bgWaterText.loadFromFile("background_water.png");
    bgBeachText.loadFromFile("background_beach.png");
    bgObjectsText.loadFromFile("background_objects.png");
    sf::Sprite bgWaterSprite(bgWaterText);
    sf::Sprite bgBeachSprite(bgBeachText);
    sf::Sprite bgObjectSprite(bgObjectsText);

    //Creating the bobber
    Bobber bobber;

    while (window.isOpen())
    {
        //Event Queue
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            //Checking for mouse button input
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                //Left mouse button
                if (mousePressed->button == sf::Mouse::Button::Left 
                    && water.getBounds().getGlobalBounds().contains({ static_cast<float>(mousePressed->position.x),  static_cast<float>(mousePressed->position.y) }))
                {
                    bobber.timerEnd(); //ensures the previous timer was stopped.
                    bobber.setPosition({ static_cast<float>(mousePressed->position.x),  static_cast<float>(mousePressed->position.y) });
                    bobber.startTimer();

                    //Debugging
                    cout << "New bobber position: " << bobber.getPosition().x << " " << bobber.getPosition().y << std::endl;
                }
            }
        }

        //Spawning fish
        if (water.getFishCount() < water.getMaxFish())
        {
            while (water.getFishCount() < water.getMaxFish())
            {
                //Spawn fish
                water.spawnRandomFish();
                water.incrementFishCount();
            }
        }

        window.clear();

        window.draw(bgWaterSprite);
        
        //wrangle.draw_scene(bass, window);

        for (auto& fishPtr : water.getFishPopulation())
        {
            fishPtr->wander(water.getBounds());
            fishPtr->draw_water_sprite(window); 
        }

        bobber.draw_scene(window);

        //bass.draw_water_sprite(window);

        //Rendow beach objects in front of water elements
        window.draw(bgBeachSprite);
        window.draw(bgObjectSprite);

        window.display();

    }

}