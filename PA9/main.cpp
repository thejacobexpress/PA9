#include <SFML/Graphics.hpp>
#include "Bass.hpp"
#include "Wrangle.hpp"
#include "Bobber.hpp"
#include "WaterBody.hpp"
#include "MerchantMenu.h"
#include "Test.h"

enum class GameState //For game states
{
    Playing, Merchant
};

int main()
{
    std::srand(std::time(NULL));

    float scale = 1;

    //Player variables
    int currency = 0, rodLevel = 0, timerLevel = 0;
    
    //Window
    sf::Vector2f defaultWindowSize({ 1280, 720 });
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "SFML (Savage Fish Mayhem Live)", sf::Style::Titlebar | sf::Style::Close);
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

    //Creating Merchant
    MerchantMenu merchantMenu(defaultWindowSize);

    Wrangle* wrangle = nullptr;
    Fish* fish = nullptr;
    int fishIndex = -1;

    //Start game
    GameState currentState = GameState::Playing;

    //For Testing
    //Test::runAllTests();

    while (window.isOpen())
    {

        //Event Queue
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            //Checking for keyboard input
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::M)
                {
                    if (currentState == GameState::Playing)
                    {
                        currentState = GameState::Merchant;
                    }
                    else
                    {
                        currentState = GameState::Playing;
                    }
                }
            }

            //Checking for mouse button input
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                sf::Vector2f clickPosition(static_cast<float>(mousePressed->position.x), static_cast<float>(mousePressed->position.y));

                //Merchant logic
                if (currentState == GameState::Merchant)
                {
                    merchantMenu.handleButtonClicks(clickPosition, currency, rodLevel, timerLevel, bobber);
                }
                else if (currentState == GameState::Playing)
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
        }

        //If the game is playing, run the logic for gameplay
        if (currentState == GameState::Playing)
        {
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
                bobber.setHasFish(false);
                bobber.startTimer();
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
        }

        //If the game requires a menu
        sf::Vector2i mousePositionInWindow = sf::Mouse::getPosition(window);
        sf::Vector2f mousePositionAsFloat = (static_cast<sf::Vector2f>(mousePositionInWindow));

        if (currentState == GameState::Merchant)
        {
            merchantMenu.update(mousePositionAsFloat);
            window.draw(bgWaterSprite);
            window.draw(bgBeachSprite);
            window.draw(bgObjectSprite);
            merchantMenu.drawWindow(window);
            merchantMenu.drawWindow(window, currency, rodLevel, timerLevel);

        }


        window.display();

    }

}