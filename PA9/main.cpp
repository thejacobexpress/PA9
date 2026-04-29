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
    window.setFramerateLimit(60);

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

    Wrangle* wrangle = nullptr;
    Fish* fish = nullptr;
    int fishIndex = -1;

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
                    && water.getBounds().getGlobalBounds().contains({ static_cast<float>(mousePressed->position.x),  static_cast<float>(mousePressed->position.y) })
                    && !bobber.getTimerRunning())
                {
                    bobber.setPosition({ static_cast<float>(mousePressed->position.x),  static_cast<float>(mousePressed->position.y) });
                    bobber.startTimer();
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

        //Running fish checks
        Fish* fishPtr = nullptr;
        for (int i = 0; i < water.getFishCount(); i++)
        {
            fishPtr = water.getFishPopulation()[i].get();
            //If the fish is on the bobber, the bobber can catch, & the bobber does not have a fish
            if (bobber.getBobberSprite().getGlobalBounds().contains(fishPtr->getWaterPos())
                && bobber.getCanCatch()
                && !bobber.getHasFish())
            {
                fishPtr->setOnRod(true);
                bobber.setHasFish(true);
                fishIndex = i;
            }
            //Otherwise, set on rod to false
            else if (!bobber.getHasFish() /*bobber does not have fish*/)
            {
                fishPtr->setOnRod(false);
                bobber.setHasFish(false);
            }

            //If the fish is not on the rod, let it move
            if (!fishPtr->getOnRod())
            {
                fishPtr->wander(water.getBounds());
            }

            fishPtr->draw_water_sprite(window); 
        }

        bobber.draw_scene(window);

        //bass.draw_water_sprite(window);

        //Rendow beach objects in front of water elements
        window.draw(bgBeachSprite);
        window.draw(bgObjectSprite);

        // Wrangle logic
        if (wrangle != nullptr && wrangle->getDel()) {
            delete wrangle;
            wrangle = nullptr;
            fish = nullptr;
            fishIndex = -1;
        }
        else if (fishIndex != -1) {
            if (wrangle == nullptr) {

                for (int i = 0; i < water.getFishCount(); i++) {
                    if (fishIndex == i) {
                        fish = water.getFishPopulation()[i].get();
                        break;
                    }
                }

                wrangle = new Wrangle(fish, window, scale);
                wrangle->draw_scene(fish, window);
            }
            else {
                wrangle->draw_scene(fish, window);
            }
        }

        window.display();

    }

}