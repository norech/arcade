#include <iostream>

#include "Loader.hpp"
#include "Manager.hpp"
#include "spc/game/IGame.hpp"
#include "spc/graphic/IGraphic.hpp"

int main()
{
    arc::core::Manager manager;

    manager.loadGame("./lib/arcade_pacman.so");
    manager.loadGraphic("./lib/arcade_sdl2.so");

    manager.init();
    while (manager.canUpdate()) {
        manager.update();
    }
    manager.destroy();
}
