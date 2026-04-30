#pragma once
#include "Button.h"
#include "Perch.hpp"
#include "Salmon.hpp"
#include <iostream>

class Test
{
public:
    //Runs all test functions and prints to console
    static void runAllTests();

private:
    //Test 1: Verifies the locking mechanism works and updates the state correctly
    static bool testButtonLocking();

    //Test 2: Verifies the state transitions between Idle, Hover, and Pushed
    static bool testButtonStateUpdate();

    //Test 3: Verifies the boundary detection of the button sprite
    static bool testButtonBounds();

    //Test 4:
    static bool testPerchSpawnPosition();

    //Test 5:
    static bool testSalmonSpawnPosition();


};