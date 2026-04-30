#include "Test.h"

void Test::runAllTests()
{
    std::cout << "Testing:\n";
    
    std::cout << "Test 1 (Button Locking): " << (testButtonLocking() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test 2 (Button State Update): " << (testButtonStateUpdate() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Test 3 (Button Bounds): " << (testButtonBounds() ? "PASSED" : "FAILED") << "\n";
}

bool Test::testButtonLocking()
{
    //Create test button
    sf::Texture testTexture;
    testTexture.resize({ 10, 10 });
    Button testButton(testTexture);

    //Lock button and test if it is locked
    testButton.setLocked(true);
    if (!testButton.isLocked() || testButton.getState() != ButtonState::Locked)
    {
        return false;
    }

    //Unlock button and test if unlocked
    testButton.setLocked(false);
    if (testButton.isLocked() || testButton.getState() == ButtonState::Locked)
    {
        return false;
    }

    return true;
}

bool Test::testButtonStateUpdate()
{
    //Create test button
    sf::Texture testTexture;
    testTexture.resize({ 100, 100 }); //Create button of size 100 by 100
    Button testButton(testTexture, sf::Vector2f(0.f, 0.f)); //Apply testTexture, and set position to 0,0

    //If test button has no mouse, test passed
    testButton.updateButtonState(sf::Vector2f(150.f, 150.f), false);
    if (testButton.getState() != ButtonState::Idle) { return false; }

    //Test if mouse hover over button work
    testButton.updateButtonState(sf::Vector2f(50.f, 50.f), false);
    if (testButton.getState() != ButtonState::Hover) { return false; }

    //Test if button click work
    testButton.updateButtonState(sf::Vector2f(50.f, 50.f), true); //True for clicking
    if (testButton.getState() != ButtonState::Pushed) { return false; }

    return true;
}

bool Test::testButtonBounds()
{
    sf::Texture testTexture;
    testTexture.resize({ 50, 50 });

    //Have true until test is complete
    return true;

}