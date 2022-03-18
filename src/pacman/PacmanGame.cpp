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
            if (event.keyboardInput.keyCode == KeyCode::Z) {
                std::cout << "press Z" << std::endl;
                _playerY--;
            }
            if (event.keyboardInput.keyCode == KeyCode::S) {
                std::cout << "press S" << std::endl;
                _playerY++;
            }
            if (event.keyboardInput.keyCode == KeyCode::Q) {
                std::cout << "press Q" << std::endl;
                _playerX--;
            }
            if (event.keyboardInput.keyCode == KeyCode::D) {
                std::cout << "press D" << std::endl;
                _playerX++;
            }
        }
    }
}

bool PacmanGame::mustLoadAnotherGraphic() const
{
    return this->_mustLoadAnotherGraphic;
}

void PacmanGame::render()
{
    _graphic->clear();
    _canvas->startDraw();

    _canvas->drawPoint(_playerX, _playerY, _palette[0]);

    _canvas->endDraw();
    _graphic->render();
}

void PacmanGame::loadGraphic(grph::IGraphic* graphic)
{
    _graphic.reset(graphic);
    graphic->loadCanvas(_canvas);
}

void PacmanGame::unloadGraphic()
{
    _graphic->unloadCanvas(_canvas);
    _graphic.reset();
}

void PacmanGame::destroy() { }

} // namespace arc::game
