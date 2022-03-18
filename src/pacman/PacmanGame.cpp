#include "PacmanGame.hpp"
#include "spc/common/KeyCode.hpp"
#include <iostream>

namespace arc::game {

void PacmanGame::init()
{
    _palette.setColor(0, 'P', GREEN);
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
            if (event.keyboardInput.keyCode == KeyCode::P)
                _mustLoadAnotherGraphic = true;
            if (event.keyboardInput.keyCode == KeyCode::Z) {
                _playerY--;
                std::cout << "z is pressed\n" << std::flush;
            }
            if (event.keyboardInput.keyCode == KeyCode::S) {
                _playerY++;
                std::cout << "s is pressed\n" << std::flush;
            }
            if (event.keyboardInput.keyCode == KeyCode::Q) {
                _playerX--;
                std::cout << "q is pressed\n" << std::flush;
            }
            if (event.keyboardInput.keyCode == KeyCode::D) {
                _playerX++;
                std::cout << "d is pressed\n" << std::flush;
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

    _canvas->drawPoint(this->_playerX, this->_playerY, this->_palette[0]);

    _canvas->endDraw();
    _graphic->render();
}

void PacmanGame::loadGraphic(grph::IGraphic* graphic)
{
    this->_mustLoadAnotherGraphic = false;
    _graphic = graphic;
    _graphic->loadCanvas(_canvas);
}

void PacmanGame::unloadGraphic() { this->_graphic->unloadCanvas(_canvas); }

void PacmanGame::destroy() { }

} // namespace arc::game
