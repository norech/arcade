#include <iostream>

#include "spc/game/IGame.hpp"
#include "spc/graphic/IGraphic.hpp"

#include "Loader.hpp"

using IGraphic = arc::grph::IGraphic;
using IGame = arc::game::IGame;
using GraphicLoader = arc::core::Loader<IGraphic>;
using GameLoader = arc::core::Loader<IGame>;

int main(void)
{
    std::array<std::string, 3> graphics
        = { "./lib/arcade_sdl2.so", "./lib/arcade_ncurses.so",
           "./lib/arcade_sfml.so" };
    std::array<std::string, 2> games = {"./lib/arcade_pacman.so", "./lib/arcade_nibbler.so"};
    IGame* game = GameLoader::load("./lib/arcade_nibbler.so");

    IGraphic* graphic = GraphicLoader::load("./lib/arcade_sdl2.so");
    int currentGraphicId = 0;

    game->init();
    graphic->init();

    game->loadGraphic(graphic);
    while (graphic->isOpen()) {
        game->update(graphic->tick());
        game->render();
        if (game->mustLoadAnotherGraphic()) {
            game->unloadGraphic();
            graphic->destroy();
            GraphicLoader::unload(graphic);

            currentGraphicId = (currentGraphicId + 1) % graphics.size();
            graphic = GraphicLoader::load(graphics[currentGraphicId]);
            graphic->init();
            game->loadGraphic(graphic);
        }
    }
    game->unloadGraphic();

    graphic->destroy();
    game->destroy();

    GraphicLoader::unload(graphic);
    GameLoader::unload(game);

    return 0;
}
