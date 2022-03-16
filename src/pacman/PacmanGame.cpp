#include "PacmanGame.hpp"
#include "spc/common/KeyCode.hpp"
#include <iostream>

namespace arc::game {

void PacmanGame::init()
{
    _palette.setColor(0, 'P', YELLOW);
    _palette.setColor(1, 'G', RED);
}

void PacmanGame::update(float dt [[maybe_unused]])
{
    Event event;
    while (_graphic->pollEvent(event)) {

        if (event.type == Event::QUIT) {
            _graphic->close();
        }

        if (event.type == Event::KEYDOWN) {
            if (event.keyboardInput.keyCode == KeyCode::Z)
                _playerY--;
            if (event.keyboardInput.keyCode == KeyCode::S)
                _playerY++;
            if (event.keyboardInput.keyCode == KeyCode::Q)
                _playerX--;
            if (event.keyboardInput.keyCode == KeyCode::D)
                _playerX++;
        }
    }
}

void PacmanGame::render()
{
    std::cout << "ici1\n" << std::flush;

    _canvas->startDraw();

    std::cout << "ici2\n" << std::flush;

    _canvas->drawPoint(_playerX, _playerY, _palette[0]);
    std::cout << "ici3\n" << std::flush;
    _canvas->endDraw();
    std::cout << "ici4\n" << std::flush;
    _graphic->render();
    std::cout << "ici5\n" << std::flush;
}

void PacmanGame::loadGraphic(grph::IGraphic* graphic)
{
    _graphic.reset(graphic);
}

void PacmanGame::unloadGraphic() { _graphic.reset(); }

void PacmanGame::destroy() { }

} // namespace arc::game
