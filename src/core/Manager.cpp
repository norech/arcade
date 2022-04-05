#include "./Manager.hpp"
#include "./Loader.hpp"
#include "./ManagerError.hpp"
#include "spc/common/KeyCode.hpp"

namespace arc::core {

using GraphicLoader = arc::core::Loader<grph::IGraphic>;
using GameLoader = arc::core::Loader<game::IGame>;

void Manager::loadGame(const std::string& game)
{
    if (_game != nullptr) {
        throw ManagerError("Game already loaded");
    }
    _game = GameLoader::load(game);
    _game->init();
}

void Manager::loadGraphic(const std::string& graphic)
{
    if (_graphic != nullptr) {
        if (_game != nullptr)
            _game->unloadGraphic();
        _graphic->destroy();
        GraphicLoader::unload(_graphic);
    }
    _graphic = GraphicLoader::load(graphic);
    _graphic->init();

    if (_game != nullptr)
        _game->loadGraphic(_graphic);
}

game::IGame* Manager::getGame() { return _game; }

grph::IGraphic* Manager::getGraphic() { return _graphic; }

void Manager::setGraphic(grph::IGraphic* graphic) { _graphic = graphic; }

void Manager::setGame(game::IGame* game) { _game = game; }

void Manager::init()
{
    if (_graphic == nullptr) {
        throw ManagerError("Graphic not loaded");
    }
    if (_game == nullptr) {
        throw ManagerError("Game not loaded");
    }
    _game->setManager(this);
    _game->loadGraphic(_graphic);
}

void Manager::destroy()
{
    _game->unloadGraphic();
    _graphic->destroy();
    _game->destroy();
    GraphicLoader::unload(_graphic);
    GameLoader::unload(_game);
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

} // namespace arc::core
