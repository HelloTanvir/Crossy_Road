#include "Game.h"

int main()
{
    // Initialize random seed
    srand(static_cast<unsigned>(time(0)));

    Game game;

    while (game.running())
    {
        game.update();
        game.render();
    }

    return 0;
}