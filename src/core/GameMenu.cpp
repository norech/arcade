
#include "GameMenu.hpp"
#include "../common/VectorInt.hpp"
#include "Manager.hpp"
#include "spc/common/KeyCode.hpp"
#include <iostream>

namespace arc::game {

void GameMenu::init()
{
    arc::core::Manager* manager = dynamic_cast<arc::core::Manager*>(_manager);

    manager->listGames(_games);
    manager->listGraphics(_graphics);
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
            _gameIndex = _gameIndex % _games.size();
        }
    }
}

bool GameMenu::mustLoadAnotherGraphic() const { return false; }

const IColor& GameMenu::getGameTextColor(int index)
{
    const IColor& selectedColor = this->_palette[0];
    const IColor& textColor = this->_palette[1];

    if (index == _gameIndex)
        return selectedColor;
    return textColor;
}

const IColor& GameMenu::getGraphicTextColor(int index)
{
    const IColor& selectedColor = this->_palette[0];
    const IColor& textColor = this->_palette[1];

    if (index == _gameIndex)
        return selectedColor;
    return textColor;
}

void GameMenu::render()
{
    _graphic->clear();
    _canvas->startDraw();

    _canvas->drawText(17, 5, "ARCADE", this->_palette[1]);

    for (unsigned int i = 0; i < _games.size(); i++) {
        const IColor& textColor = getGameTextColor(i);
        _canvas->drawText(1, 15 + i, _games[i], textColor);
    }

    for (unsigned int i = 0; i < _graphics.size(); i++) {
        const IColor& textColor = getGraphicTextColor(i);
        _canvas->drawText(20, 15 + i, _graphics[i], textColor);
    }

    _canvas->drawText(
        5, 27, "Press arrows to select a game", this->_palette[1]);
    _canvas->drawText(5, 28, "Press Enter to confirm", this->_palette[1]);

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
    return "./lib/arcade_nibbler.so";
}

const std::string GameMenu::getSelectedGraphicPath() const
{
    return "./lib/arcade_sdl2.so";
}

bool GameMenu::hasSelectedGame() const { return _hasSelectedGame; }

} // namespace arc::game
