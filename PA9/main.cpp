#include <SFML/Graphics.hpp>
#include "Bass.hpp"

int main()
{
    Bass f = Bass();

    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "SFML (Savage Fish Mayhem Live)");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }



        window.clear();
        window.draw(f.getWaterSprite());
        window.display();
    }
}