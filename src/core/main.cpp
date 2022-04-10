#include <iostream>

#include "Loader.hpp"
#include "LoaderError.hpp"
#include "Manager.hpp"
#include "ManagerError.hpp"
#include "spc/game/IGame.hpp"
#include "spc/graphic/IGraphic.hpp"

#include "GameMenu.hpp"

void showGameMenu(arc::core::Manager& manager, arc::game::GameMenu& gameMenu,
    const std::string& graphicPath)
{
    manager.loadGame(&gameMenu);
    manager.loadGraphic(graphicPath);

    while (manager.canUpdate()) {
        manager.update();
    }

    if (!gameMenu.hasSelectedGame()) {
        manager.destroy();
        return;
    }
    manager.unloadGraphic();
    manager.unloadGame();
}

void runArcade(const std::string& graphic)
{
    arc::core::Manager manager;
    arc::game::GameMenu gameMenu;
    manager.init();

    showGameMenu(manager, gameMenu, graphic);
    if (!gameMenu.hasSelectedGame()) {
        manager.destroy();
        return;
    }
    manager.setPlayerName(gameMenu.getPlayerName());
    manager.loadGame(gameMenu.getSelectedGamePath());
    manager.loadGraphic(gameMenu.getSelectedGraphicPath());

    while (manager.canUpdate()) {
        manager.update();
    }
    manager.destroy();
}

int main(int ac, char* av[])
{
    if (ac != 2) {
        std::cout << "Usage: " << av[0] << " [graphical_library.so]"
                  << std::endl
                  << "" << std::endl
                  << "Common game input:" << std::endl
                  << " ZQSD / Arrows\t\tMove" << std::endl
                  << " I / Enter\t\tConfirm" << std::endl
                  << " R\t\t\tRestart game" << std::endl
                  << "Core input:" << std::endl
                  << " K\t\t\tExit game" << std::endl
                  << " O\t\t\tPrevious graphical library" << std::endl
                  << " P\t\t\tNext graphical library" << std::endl;
        return 84;
    }

    try {
        runArcade(av[1]);
    } catch (const arc::core::ManagerError& ex) {
        std::cout << "Internal error: " << ex.what() << std::endl;
        return 84;
    } catch (const arc::core::LoaderError& ex) {
        std::cout << "Can't load library: " << ex.what() << std::endl;
        return 84;
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
        return 84;
    }
}
