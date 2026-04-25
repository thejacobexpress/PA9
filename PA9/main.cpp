#include <SFML/Graphics.hpp>
#include "Bass.hpp"
#include "Wrangle.hpp"
#include "MainMenu.h"
#include "MerchantMenu.h"

enum class GameState //For game states
{
    MainMenu, Playing, Merchant
};

int main()
{
    float scale = 1.5;

	sf::Vector2f defaultWindowSize({ 1280, 720 });
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "SFML (Savage Fish Mayhem Live)");
	window.setFramerateLimit(180); //Limit the frame rate

	MainMenu mainMenu(defaultWindowSize);
    MerchantMenu merchantMenu(defaultWindowSize);
	
    Bass bass;
	Wrangle wrangle(bass, window, scale);

    while (window.isOpen()) //Loop while the window is open
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) //To close the window
                window.close();

            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) //For key pressign detection
            {
                //Menu-Playing logic
                if (keyPressed->code == sf::Keyboard::Key::Escape) //If Escape pressed
                {
                    if (currentState == GameState::Playing) //And the game is playing
                    {
                        currentState = GameState::MainMenu; //Switch to MainMenu
                    }
                    else //Else, the game is already in the menu (not GameState::Playing)
                    {
                        currentState = GameState::Playing; //Switch back to playing
                    }
                }
                else if (keyPressed->code == sf::Keyboard::Key::M)
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
        }
        
        //If the game is in Playing state, Play
        if (currentState == GameState::Playing)
        {
            //Code for playing game
        }

        //If the game requires a menu
        sf::Vector2i mousePositionInWindow = sf::Mouse::getPosition(window);
        sf::Vector2f mousePositionAsFloat = (static_cast<sf::Vector2f>(mousePositionInWindow));

        if (currentState == GameState::MainMenu)
        {
            mainMenu.update(mousePositionAsFloat); //Send mouse position for menu button logic
            if (mainMenu.isStartPushed())
            {
                currentState = GameState::Playing;
            }
            if (mainMenu.isCreditsPushed())
            {
                //Maybe add this if time allows???
            }
            if (mainMenu.isQuitPushed())
            {
                window.close();
            }
        }
        else if (currentState == GameState::Merchant)
        {
            merchantMenu.update(mousePositionAsFloat);
            if (merchantMenu.isUpgradeRodSpeedPushed())
            {
                //Upgrade rod speed
            }
            if (merchantMenu.isSellFishPushed())
            {
                //Sell fish
            }
        }

        //Rendering window
        window.clear(sf::Color::Black); //Background colour

        if (currentState == GameState::Merchant)
        {
            merchantMenu.drawWindow(window);
        }
        else if (currentState == GameState::MainMenu)
        {
            mainMenu.drawWindow(window);
        }

        window.display();
    }
}
