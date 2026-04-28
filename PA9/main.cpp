#include "MainMenu.h"
#include "MerchantMenu.h"
#include <iostream>

enum class GameState //For game states
{
    MainMenu, Playing, Merchant
};

int main()
{
    sf::Vector2f defaultWindowSize({ 1280, 720 });
    sf::RenderWindow window(sf::VideoMode( static_cast<sf::Vector2u>(defaultWindowSize) ), "SFML (Savage Fish Mayhem Live)"); //Creates the initial window
    window.setFramerateLimit(180); //Limit the frame rate for stability (Probably)

    int rodLevel = 0, timerLevel = 0, money = 0;

    //MainMenu mainMenu(defaultWindowSize);
    MerchantMenu merchantMenu(defaultWindowSize);

    bool previousButtonState = false, currentButtonState = false;

    //Start Game
    GameState currentState = GameState::Playing;

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
                        currentState = GameState::Playing; //And so, switch back to playing
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
            else if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseClick->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f clickPosition(static_cast<float>(mouseClick->position.x), static_cast<float>(mouseClick->position.y));
                    
                    if (currentState == GameState::Merchant)
                    {
                        merchantMenu.handleButtonClicks(clickPosition, money, rodLevel, timerLevel);
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

        //if (currentState == GameState::MainMenu)
        //{
        //    mainMenu.update(mousePositionAsFloat);
        //    if (mainMenu.isStartPushed())
        //    {
        //        currentState = GameState::Playing;
        //    }
        //    if (mainMenu.isCreditsPushed())
        //    {
        //        //Maybe add this if time allows???
        //    }
        //    if (mainMenu.isQuitPushed())
        //    {
        //        window.close();
        //    }
        //}
        if (currentState == GameState::Merchant)
        {
            merchantMenu.update(mousePositionAsFloat);
        }

        //Rendering window
        window.clear(sf::Color::Blue); //Background colour

        if (currentState == GameState::Merchant)
        {
            merchantMenu.drawWindow(window);
            merchantMenu.drawWindow(window, money, rodLevel, timerLevel);
        }
        /*else if (currentState == GameState::MainMenu)
        {
            mainMenu.drawWindow(window);
        }*/

        window.display();
    }
}