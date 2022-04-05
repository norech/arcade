#include "./Manager.hpp"
#include "./Loader.hpp"
#include "./ManagerError.hpp"
#include "spc/common/KeyCode.hpp"

namespace arc::core {

void Manager::loadGame(const std::string& game)
{
    if (_game != nullptr) {
        throw ManagerError("Game already loaded");
    }
    _game = core::Loader<game::IGame>::load(game);
    _game->init();
}

void Manager::loadGraphic(const std::string& graphic)
{
    if (_graphic != nullptr) {
        _game->unloadGraphic();
        _graphic->destroy();
        core::Loader<grph::IGraphic>::unload(_graphic);
    }
    _graphic = core::Loader<grph::IGraphic>::load(graphic);
    _graphic->init();
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
    core::Loader<grph::IGraphic>::unload(_graphic);
    core::Loader<game::IGame>::unload(_game);
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
        _mustLoadAnotherGraphic = false;
        _currentGraphicId = (_currentGraphicId + 1) % _graphicPaths.size();
        loadGraphic(_graphicPaths[_currentGraphicId]);
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
