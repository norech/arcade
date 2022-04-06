
#include "GameMenu.hpp"
#include "../common/VectorInt.hpp"
#include "spc/common/KeyCode.hpp"
#include <iostream>

namespace arc::game {

void GameMenu::init()
{
    _palette.setColor(0, '>', YELLOW);
    _palette.setColor(1, ' ', WHITE);
}

void GameMenu::update(float dt [[maybe_unused]])
{
    Event event;
    while (_manager->pollEvent(event)) {
        if (event.type == Event::QUIT) {
            _graphic->close();
        }
        if (event.type == Event::KEYDOWN) {
            if (event.keyboardInput.keyCode == KeyCode::Z)
                _gameIndex--;
            if (event.keyboardInput.keyCode == KeyCode::S)
                _gameIndex++;
            if (event.keyboardInput.keyCode == KeyCode::I) {
                _hasSelectedGame = true;
                _graphic->close();
            }
        }
    }
}

bool GameMenu::mustLoadAnotherGraphic() const { return false; }

void GameMenu::render()
{
    const IColor& selectedColor = this->_palette[0];
    const IColor& textColor = this->_palette[1];
    _graphic->clear();
    _canvas->startDraw();

    _canvas->drawText(1, 1, "test 1", selectedColor);
    _canvas->drawText(1, 3, "test 2", textColor);

    _canvas->endDraw();
    _graphic->render();
}

void GameMenu::loadGraphic(grph::IGraphic* graphic)
{
    _graphic = graphic;
    _graphic->loadCanvas(_canvas);
}

void GameMenu::unloadGraphic() { this->_graphic->unloadCanvas(_canvas); }

void GameMenu::destroy() { }

void GameMenu::setManager(IManager* manager) { _manager = manager; }

const std::string GameMenu::getSelectedGamePath() const
{
    return "./lib/arcade_pacman.so";
}

const std::string GameMenu::getSelectedGraphicPath() const
{
    return "./lib/arcade_sdl2.so";
}

bool GameMenu::hasSelectedGame() const { return _hasSelectedGame; }

} // namespace arc::game
