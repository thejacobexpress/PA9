# include "Wrangle.hpp"
# include <random>

Wrangle::Wrangle(Fish* fish, sf::RenderWindow& window, float scale) {
    if (fish == nullptr) {
        return;
    }

    barText.loadFromFile("reel.png");
    barSprite = sf::Sprite(barText);
    barSprite.setOrigin({ barSprite.getLocalBounds().size.x / 2, barSprite.getLocalBounds().size.y / 2 });
    barSprite.setPosition({ 200, static_cast<float>(window.getSize().y / 2) });

    fish->getWrangleSprite().setPosition({ 200 - fish->getWrangleSprite().getGlobalBounds().size.x/2, static_cast<float>(window.getSize().y / 2)});

    targetBar = sf::RectangleShape({ static_cast<float>(window.getSize().x/35), 100});
    targetBar.setOrigin({ targetBar.getLocalBounds().size.x / 2, targetBar.getLocalBounds().size.y / 4 });
    targetBar.setPosition({ 200, static_cast<float>(window.getSize().y / 4) });
	targetBar.setFillColor(sf::Color::Green);

    progressBar = sf::RectangleShape({ 12, 0});
    progressBar.setOrigin({ targetBar.getLocalBounds().size.x / 2, targetBar.getLocalBounds().size.y / 2 });
    progressBar.setPosition({ 260, static_cast<float>(window.getSize().y / 3.6) });
    progressBar.setFillColor(sf::Color::Blue);

    window.draw(barSprite);
    window.draw(targetBar);
    window.draw(progressBar);
    window.draw(fish->getWrangleSprite());
}

void Wrangle::draw_scene(Fish*fish, sf::RenderWindow& window) {
    if (progress >= 100 && !wrangleDone) {
        cout << "You caught the fish!" << std::endl;
        wrangleDone = true;
        caught = true;
        startTime = std::chrono::high_resolution_clock::now();
        fish->getCaughtSprite().setPosition({ 600, 200 });
        window.draw(fish->getCaughtSprite());
    }
    else if (progress >= 100 && wrangleDone) {
		if(caught) window.draw(fish->getCaughtSprite());
        window.draw(barSprite);
        window.draw(targetBar);
        window.draw(progressBar);
        // Wait 5 seconds
        if (std::chrono::high_resolution_clock::now() - startTime >= std::chrono::seconds(5)) {
            del = true;
			fish->getWaterSprite().setColor(sf::Color::Transparent);
        }
    }
    else if (progress <= 0) {
        cout << "The fish got away!" << std::endl;
        fish->setOnRod(false);
        startTime = std::chrono::high_resolution_clock::now();
        wrangleDone = true;
    }
    else {
        move_fish(fish, window);

        if (fish->getWrangleSprite().getGlobalBounds().findIntersection(targetBar.getGlobalBounds()).has_value()) {
            progress += 0.2;
        }
        else {
            progress -= 0.1;
        }

        targetBar.move({ 0, targetBarVelocity.y });
        targetBarVelocity.y += gravityAcceleration;

        progressBar.setSize({ 12, progressBarHeight * (progress / 100) });

        // Check if the targetBar is above or below the barSprite and reverse velocity if so
        if (targetBar.getGlobalBounds().position.y <= barSprite.getGlobalBounds().position.y + 35) {
            targetBarVelocity.y = abs(targetBarVelocity.y / 2);
        }
        else if (targetBar.getGlobalBounds().position.y >= barSprite.getGlobalBounds().position.y + barSprite.getGlobalBounds().size.y - targetBar.getGlobalBounds().size.y - 35) {
            targetBarVelocity.y = -abs(targetBarVelocity.y / 2);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            targetBarVelocity.y -= userAcceleration;
        }

        window.draw(barSprite);
        window.draw(targetBar);
        window.draw(progressBar);
        window.draw(fish->getWrangleSprite());
    }

}

void Wrangle::move_fish(Fish* fish, sf::RenderWindow & window) {
    if (targetPos == -1) {
        targetPos = get_new_loc(fish, window);
        cout << targetPos << std::endl;
    }

	// Change targetPos if it is close enough to the target position
    if (abs(fish->getWrangleSprite().getPosition().y - targetPos) < 5) {
        targetPos = -1;
    }
    else if (fish->getWrangleSprite().getPosition().y >= targetPos) {
        fish->getWrangleSprite().move({ 0, -fishVelocity.y });
    }
    else if (fish->getWrangleSprite().getPosition().y <= targetPos) {
        fish->getWrangleSprite().move({ 0, fishVelocity.y });
    }

}

float Wrangle::get_new_loc(Fish* fish, sf::RenderWindow& window) {
    float newLoc = 0;

    // Generate random number
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 2);
    int rand = distrib(gen);

    float maxDist = 0;
    switch (fish->getStrength()) {
    case 1:
        maxDist = window.getSize().y / 8;
		fishVelocity = { 0, 1 };
        break;
    case 2:
        maxDist = window.getSize().y / 6;
        fishVelocity = { 0, 2 };
        break;
    case 3:
        maxDist = window.getSize().y / 4;
        fishVelocity = { 0, 3 };
        break;
    case 4:
        maxDist = window.getSize().y / 2;
        fishVelocity = { 0, 4 };
        break;
    } 

    if (rand) {
        if (fish->getWrangleSprite().getGlobalBounds().position.y - maxDist - 20 < barSprite.getGlobalBounds().position.y) {
            newLoc = barSprite.getGlobalBounds().position.y + 20;
        }
        else {
            newLoc = fish->getWrangleSprite().getGlobalBounds().position.y - maxDist + 20;
        }
    }
    else {
        if (fish->getWrangleSprite().getGlobalBounds().position.y + maxDist - fish->getWrangleSprite().getGlobalBounds().size.y + 20 > barSprite.getGlobalBounds().position.y - barSprite.getGlobalBounds().size.y) {
            newLoc = barSprite.getGlobalBounds().position.y + barSprite.getGlobalBounds().size.y - fish->getWrangleSprite().getGlobalBounds().size.y - 20;
        }
        else {
            newLoc = fish->getWrangleSprite().getGlobalBounds().position.y + maxDist - 20;
        }
    }

    return newLoc;
}

bool Wrangle::getDel() {
    return del;
}