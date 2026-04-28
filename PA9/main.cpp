#include <SFML/Graphics.hpp>
#include "Bass.hpp"
#include "Wrangle.hpp"

int main()
{
    float scale = 1;
    
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "SFML (Savage Fish Mayhem Live)");

    Bass bass;
    Wrangle* wrangle = new Wrangle(bass, window, scale);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        if (!wrangle->getDel()) {
            wrangle->draw_scene(bass, window);
        }
        else {
            delete wrangle;
        }

        window.display();

    }

}