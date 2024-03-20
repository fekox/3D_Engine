#include "game.h"

using namespace baseEngine;

int main(void)
{
    int width = 1920;
    int height = 1080;

    const char* windowName = "Engine_3D";

    Game* game;

    game = new Game(width, height, windowName);

    game->gameLoop();

    delete game;
    return 0;
}