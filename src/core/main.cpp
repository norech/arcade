#include <iostream>

#include "Loader.hpp"
#include "LoaderError.hpp"
#include "Manager.hpp"
#include "ManagerError.hpp"
#include "spc/game/IGame.hpp"
#include "spc/graphic/IGraphic.hpp"

#include "GameMenu.hpp"

bool showGameMenu(arc::core::Manager& manager, arc::game::GameMenu& gameMenu)
{
    manager.loadGame(&gameMenu);

    while (manager.canUpdate()) {
        manager.update();
    }

    if (!gameMenu.hasSelectedGame()) {
        return false;
    }
    manager.unloadGame();
    return true;
}

void runArcade(const std::string& graphic)
{
    bool isBackToMenu = false;
    arc::core::Manager manager;
    arc::game::GameMenu gameMenu;

    manager.init();
    manager.loadGraphic(graphic);

    do {
        if (!showGameMenu(manager, gameMenu))
            break;

        if (!gameMenu.hasSelectedGame())
            break;

        manager.unloadGraphic();
        manager.setPlayerName(gameMenu.getPlayerName());
        manager.loadGraphic(gameMenu.getSelectedGraphicPath());
        manager.loadGame(gameMenu.getSelectedGamePath());

        while (manager.canUpdate()) {
            manager.update();
        }
        manager.unloadGame();
        isBackToMenu = manager.isBackToMenu();
        if (isBackToMenu)
            manager.reloadCurrentGraphic();
    } while (isBackToMenu);

    manager.destroy();
}

int main(int ac, char* av[])
{
    if (ac != 2 || *av[1] == '-') {
        std::cout << "Usage: " << av[0] << " [graphical_library.so]"
                  << std::endl
                  << "" << std::endl
                  << "Common game input:" << std::endl
                  << " ZQSD / Arrows\t\tMove" << std::endl
                  << " Enter\t\t\tConfirm" << std::endl
                  << " R\t\t\tRestart game" << std::endl
                  << "Core input:" << std::endl
                  << " K\t\t\tExit game" << std::endl
                  << " O\t\t\tPrevious graphical library" << std::endl
                  << " P\t\t\tNext graphical library" << std::endl
                  << " L\t\t\tPrevious game" << std::endl
                  << " M\t\t\tNext game" << std::endl
                  << " I\t\t\tGo back to game menu" << std::endl;
        return 84;
    }

    try {
        runArcade(av[1]);
    } catch (const arc::core::ManagerError& ex) {
        std::cerr << "Internal error: " << ex.what() << std::endl;
        return 84;
    } catch (const arc::core::LoaderError& ex) {
        std::cerr << "Can't load library: " << ex.what() << std::endl;
        return 84;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 84;
    }
}
