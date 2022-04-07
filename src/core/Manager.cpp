#include "./Manager.hpp"
#include "./Loader.hpp"
#include "./ManagerError.hpp"
#include "spc/common/KeyCode.hpp"

namespace arc::core {

using GraphicLoader = arc::core::Loader<grph::IGraphic>;
using GameLoader = arc::core::Loader<game::IGame>;

void Manager::loadGame(arc::game::IGame* game)
{
    if (_game != nullptr) {
        throw ManagerError("Game already loaded");
    }
    if (game == nullptr) {
        throw ManagerError("Game is null");
    }
    _game = game;
    _game->setManager(this);
    game->init();
    _isGameFromLoader = false;
}

void Manager::loadGame(const std::string& game)
{
    if (_game != nullptr) {
        throw ManagerError("Game already loaded");
    }
    _game = GameLoader::load(game);
    _game->setManager(this);
    _game->init();
    _isGameFromLoader = true;
}

void Manager::loadGraphic(const std::string& graphic)
{
    if (_game == nullptr)
        throw ManagerError("Game not yet loaded!");

    if (_graphic != nullptr) {
        _game->unloadGraphic();
        _graphic->destroy();
        GraphicLoader::unload(_graphic);
    }
    _graphic = GraphicLoader::load(graphic);
    _graphic->init();
    _isGraphicFromLoader = true;

    _game->loadGraphic(_graphic);
}

void Manager::unloadGame()
{
    if (_game == nullptr)
        throw ManagerError("Game not yet loaded!");
    if (_graphic != nullptr)
        _game->unloadGraphic();
    _game->destroy();
    if (_isGameFromLoader) {
        GameLoader::unload(_game);
    }
    _game = nullptr;
}

void Manager::unloadGraphic()
{
    if (_graphic == nullptr)
        throw ManagerError("Graphic not yet loaded!");
    if (_game != nullptr)
        _game->unloadGraphic();
    _graphic->destroy();
    if (_isGraphicFromLoader) {
        GraphicLoader::unload(_graphic);
    }
    _graphic = nullptr;
}
game::IGame* Manager::getGame() { return _game; }

grph::IGraphic* Manager::getGraphic() { return _graphic; }

void Manager::setGraphic(grph::IGraphic* graphic) { _graphic = graphic; }

void Manager::setGame(game::IGame* game) { _game = game; }

void Manager::init() { listGraphics(_graphicPaths); }

void Manager::destroy()
{
    _game->unloadGraphic();
    _graphic->destroy();
    _game->destroy();
    if (_isGameFromLoader) {
        GameLoader::unload(_game);
    }
    if (_isGraphicFromLoader) {
        GraphicLoader::unload(_graphic);
    }
    _isGraphicFromLoader = false;
    _isGameFromLoader = false;
    _game = nullptr;
    _graphic = nullptr;
}

bool Manager::canUpdate() { return _graphic->isOpen(); }

void Manager::update()
{
    if (_game == nullptr) {
        throw ManagerError("No game loaded");
    }
    if (_graphic == nullptr) {
        throw ManagerError("No graphic loaded");
    }
    _game->update(_graphic->tick());
    _game->render();
    if (_mustLoadAnotherGraphic || _game->mustLoadAnotherGraphic()) {
        _game->unloadGraphic();
        _graphic->destroy();
        GraphicLoader::unload(_graphic);
        _graphic = nullptr;

        _mustLoadAnotherGraphic = false;
        _currentGraphicId = (_currentGraphicId + 1) % _graphicPaths.size();
        _graphic = GraphicLoader::load(_graphicPaths[_currentGraphicId]);
        _graphic->init();
        _game->loadGraphic(_graphic);
    }
}

bool Manager::pollEvent(Event& input)
{
    bool event = _graphic->pollEvent(input);
    if (event && input.type == Event::KEYDOWN
        && input.keyboardInput.keyCode == KeyCode::P) {
        _mustLoadAnotherGraphic = true;
        return false;
    }
    return event;
}

void Manager::listGames(std::vector<std::string>& games)
{
    std::vector<std::string> g = { "./lib/arcade_pacman.so" };

    games.clear();
    for (auto& game : g) {
        games.push_back(game);
    }
}

void Manager::listGraphics(std::vector<std::string>& graphics)
{
    std::vector<std::string> g
        = { "./lib/arcade_sdl2.so", "./lib/arcade_sfml.so",
              "./lib/arcade_ncurses.so", "./lib/arcade_libcaca.so" };

    graphics.clear();
    for (auto& game : g) {
        graphics.push_back(game);
    }
}

} // namespace arc::core
