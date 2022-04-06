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

    manager.loadGame(&gameMenu);
    manager.loadGraphic("./lib/arcade_sdl2.so");

    manager.init();
    while (manager.canUpdate()) {
        manager.update();
    }
    manager.destroy();

    if (!gameMenu.hasSelectedGame())
        return 0;
    manager.loadGame(gameMenu.getSelectedGamePath());
    manager.loadGraphic(gameMenu.getSelectedGraphicPath());

    manager.init();
    while (manager.canUpdate()) {
        manager.update();
    }
    manager.destroy();
}
