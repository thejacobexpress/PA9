# include "Wrangle.hpp"

Wrangle::Wrangle(Fish& fish, sf::RenderWindow& window, float scale) {
    barText.loadFromFile("reel.png");
    barSprite = sf::Sprite(barText);
    barSprite.setOrigin({ barSprite.getLocalBounds().size.x / 2, barSprite.getLocalBounds().size.y / 2 });
    barSprite.setPosition({ static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2) });
    barSprite.setScale(sf::Vector2f(scale, scale));

    fish.getWrangleSprite().setScale(sf::Vector2(scale, scale));
    fish.getWrangleSprite().setPosition({ static_cast<float>(window.getSize().x / 2 - fish.getWrangleSprite().getGlobalBounds().size.x / 2), static_cast<float>(window.getSize().y / 2) });

    window.draw(barSprite);
    window.draw(fish.getWrangleSprite());
}

void Wrangle::draw_scene(Fish& fish, sf::RenderWindow& window) {
    window.draw(barSprite);
    window.draw(fish.getWrangleSprite());
}

float Wrangle::get_new_loc(Fish& fish, sf::RenderWindow& window) {
    float maxDist = 0;
    switch (fish.getStrength()) {
    case 1:
        maxDist = window.getSize().y / 4;

        break;
    case 2:
        maxDist = window.getSize().y / 3;
        break;
    case 3:
        maxDist = window.getSize().y / 2;
        break;
    case 4:
        maxDist = window.getSize().y;
        break;
    }
    return 0;
}