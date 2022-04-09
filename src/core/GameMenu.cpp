#include "GameMenu.hpp"
#include "../common/VectorInt.hpp"
#include "Loader.hpp"
#include "Manager.hpp"
#include "spc/common/KeyCode.hpp"
#include <iostream>

namespace arc::game {

using GraphicLoader = arc::core::Loader<DLType::GRAPHICAL, grph::IGraphic>;
using GameLoader = arc::core::Loader<DLType::GAME, game::IGame>;

void GameMenu::init()
{
    arc::core::Manager* manager = dynamic_cast<arc::core::Manager*>(_manager);

    manager->listGames(_games);
    manager->listGraphics(_graphics);
    _palette.setColor(0, '>', YELLOW);
    _palette.setColor(1, ' ', WHITE);
    _palette.setColor(2, ' ', BLUE);
    _palette.setColor(3, '.', BLUE);

    for (auto& game : _games) {
        _gamesNames.emplace_back(GameLoader::getName(game));
    }
    for (auto& graphic : _graphics) {
        _graphicsNames.emplace_back(GraphicLoader::getName(graphic));
    }
}

void GameMenu::update(float dt [[maybe_unused]])
{
    Event event;
    while (_graphic->pollEvent(event)) {
        if (event.type == Event::QUIT) {
            _graphic->close();
        }
        if (event.type != Event::KEYDOWN) {
            continue;
        }
        if (_showNameInput
            && event.keyboardInput.keyCode == KeyCode::BACKSPACE) {
            if (_name.length() > 0) {
                _name.pop_back();
            }
            continue;
        }
        if (event.keyboardInput.keyCode == KeyCode::ENTER) {
            if (_showNameInput) {
                _hasValidatedInput = true;
                _graphic->close();
            } else {
                _showNameInput = true;
            }
            continue;
        }
        if (_showNameInput && _name.length() < 20) {
            if (isprint(event.keyboardInput.keyCode)) {
                _name.append(1, event.keyboardInput.keyCode);
            }
        } else {
            if (event.keyboardInput.keyCode == KeyCode::Z) {
                if (_hasSelectedGame)
                    _graphicIndex--;
                else
                    _gameIndex--;
            }
            if (event.keyboardInput.keyCode == KeyCode::S) {
                if (_hasSelectedGame)
                    _graphicIndex++;
                else
                    _gameIndex++;
            }
            if (event.keyboardInput.keyCode == KeyCode::Q
                || event.keyboardInput.keyCode == KeyCode::D) {
                _hasSelectedGame = !_hasSelectedGame;
            }
        }
        _gameIndex = _gameIndex % _games.size();
        _graphicIndex = _graphicIndex % _graphics.size();
    }
}

bool GameMenu::mustLoadAnotherGraphic() const { return false; }

const IColor& GameMenu::getGameTextColor(int index)
{
    const IColor& selectedColor = this->_palette[0];
    const IColor& textColor = this->_palette[1];
    const IColor& disabledColor = this->_palette[2];

    if (index == _gameIndex)
        return _hasSelectedGame ? disabledColor : selectedColor;
    return textColor;
}

const IColor& GameMenu::getGraphicTextColor(int index)
{
    const IColor& selectedColor = this->_palette[0];
    const IColor& textColor = this->_palette[1];
    const IColor& disabledColor = this->_palette[2];

    if (index == _graphicIndex)
        return !_hasSelectedGame ? disabledColor : selectedColor;
    return textColor;
}

void GameMenu::render()
{
    _graphic->clear();
    _canvas->startDraw();

    _canvas->drawText(17, 5, "ARCADE", this->_palette[1]);

    if (_showNameInput) {
        _canvas->drawText(3, 12, "Enter your name", this->_palette[1]);
        _canvas->drawText(
            3, 15, std::string("Name: ") + _name + "_", this->_palette[0]);
    } else {
        for (int y = 10; y <= 18; y++) {
            _canvas->drawText(1, y, ".", this->_palette[3]);
            _canvas->drawText(20, y, ".", this->_palette[3]);
            _canvas->drawText(38, y, ".", this->_palette[3]);
        }
        for (int x = 1; x < 38; x++) {
            _canvas->drawText(x, 10, ".", this->_palette[3]);
            _canvas->drawText(x, 18, ".", this->_palette[3]);
        }

        for (unsigned int i = 0; i < _games.size(); i++) {
            const IColor& textColor = getGameTextColor(i);
            _canvas->drawText(3, 12 + i, _gamesNames[i], textColor);
        }

        for (unsigned int i = 0; i < _graphics.size(); i++) {
            const IColor& textColor = getGraphicTextColor(i);
            _canvas->drawText(22, 12 + i, _graphicsNames[i], textColor);
        }

        _canvas->drawText(
            3, 27, "Press arrows to select a game", this->_palette[1]);
    }

    _canvas->drawText(3, 28, "Press Enter to confirm", this->_palette[1]);

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
    return _games[_gameIndex];
}

const std::string GameMenu::getSelectedGraphicPath() const
{
    return _graphics[_graphicIndex];
}

bool GameMenu::hasSelectedGame() const { return _hasValidatedInput; }

std::string GameMenu::getPlayerName() { return _name; }

} // namespace arc::game
