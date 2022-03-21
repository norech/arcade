#include "PacmanGame.hpp"
#include "spc/common/KeyCode.hpp"
#include <iostream>

#include <iostream>

namespace arc::game {

void PacmanGame::init()
{
    _timer = 0;
    _playerX = 9;
    _playerY = 15;
    _vectorPlayerx = -1;
    _vectorPlayery = 0;
    _Binky_x = 9;
    _Binky_y = 9;
    _palette.setColor(0, 'P', YELLOW);
    _palette.setColor(1, 'B', RED);
    _palette.setColor(2, '#', BLUE);
    _map.push_back(std::string("###################"));
    _map.push_back(std::string("#        #        #"));
    _map.push_back(std::string("# ## ### # ### ## #"));
    _map.push_back(std::string("#                 #"));
    _map.push_back(std::string("# ## # ##### # ## #"));
    _map.push_back(std::string("#    #   #   #    #"));
    _map.push_back(std::string("#### ### # ### ####"));
    _map.push_back(std::string("   # #       # #   "));
    _map.push_back(std::string("#### # ## ## # ####"));
    _map.push_back(std::string("       #   #       "));
    _map.push_back(std::string("#### # ##### # ####"));
    _map.push_back(std::string("   # #       # #   "));
    _map.push_back(std::string("#### ### # ### ####"));
    _map.push_back(std::string("#    #   #   #    #"));
    _map.push_back(std::string("# ## # ##### # ## #"));
    _map.push_back(std::string("#                 #"));
    _map.push_back(std::string("# ## ### # ### ## #"));
    _map.push_back(std::string("#        #        #"));
    _map.push_back(std::string("###################"));
    
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
                _vectorPlayery = -1;
                _vectorPlayerx = 0;
            }
            if (event.keyboardInput.keyCode == KeyCode::S) {
                _vectorPlayery = 1;
                _vectorPlayerx = 0;
            }
            if (event.keyboardInput.keyCode == KeyCode::Q) {
                _vectorPlayery = 0;
                _vectorPlayerx = -1;
            }
            if (event.keyboardInput.keyCode == KeyCode::D) {
                _vectorPlayery = 0;
                _vectorPlayerx = 1;
            }
        }
    }
    _timer += dt;
    if (_playerX + _vectorPlayerx == -1) {
        _playerX = 18;
    }
    if (_playerX + _vectorPlayerx >= 19) {
        _playerX = 0;
    }
    if (_map.at(_playerY + _vectorPlayery).at(_playerX + _vectorPlayerx) == '#') {
        _vectorPlayerx = 0;
        _vectorPlayery = 0;
    }
    if (_timer >= 0.60) {
        _playerX += _vectorPlayerx;
        _playerY += _vectorPlayery;
        _timer = 0;
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

    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map.at(y).size(); x++) {
            if (_map.at(y).at(x) == '#') {
                _canvas->drawPoint(x, y, this->_palette[2]);
            }
        }
    }

    _canvas->drawPoint(this->_inky_x, this->_inky_y, this->_palette[1]);

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
