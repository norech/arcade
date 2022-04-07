#include <iostream>

#include "Loader.hpp"
#include "Manager.hpp"
#include "spc/game/IGame.hpp"
#include "spc/graphic/IGraphic.hpp"

#include "GameMenu.hpp"

int main()
{
    arc::core::Manager manager;
    arc::game::GameMenu gameMenu;
    manager.init();

    manager.loadGame(&gameMenu);
    manager.loadGraphic("./lib/arcade_sdl2.so");

    while (manager.canUpdate()) {
        manager.update();
    }

    if (!gameMenu.hasSelectedGame()) {
        manager.destroy();
        return 0;
    }
    manager.unloadGraphic();
    manager.unloadGame();
    manager.loadGame(gameMenu.getSelectedGamePath());
    manager.loadGraphic(gameMenu.getSelectedGraphicPath());

    while (manager.canUpdate()) {
        manager.update();
    }
    manager.destroy();
}
