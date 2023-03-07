// ProjectDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "game.h"

using namespace sf;

int main()
{
    // Init game engine
    Game game;

    // Game loop
    while (game.running())
    {
        game.update();
        game.render();
    }

    return 0;
}
