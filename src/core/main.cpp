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
    IGame* game = GameLoader::load("./lib/arcade_pacman.so");
    IGraphic* graphic = GraphicLoader::load("./lib/arcade_sdl2.so");

    game->init();
    graphic->init();

    game->loadGraphic(graphic);
    while (graphic->isOpen()) {
        game->update(graphic->tick());
        game->render();
    }
    game->unloadGraphic();

    graphic->destroy();
    game->destroy();

    GraphicLoader::unload(graphic);
    GameLoader::unload(game);

    return 0;
}
