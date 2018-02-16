#include "pingpong.h"

int main()
{
    PingPong Game;

    if (!Game.init()) { Game.quit(); return -1; }

    while (Game.game_loop()) {}

    Game.quit();

    return 0;
}
