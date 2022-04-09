
#include "PacmanGame.hpp"
#include "../common/VectorInt.hpp"
#include "spc/common/KeyCode.hpp"
#include <iostream>

namespace arc::game {

// clang-format off
std::vector<std::string> PacmanGame::_map = {
    "###################",
    "#        #        #",
    "# ## ### # ### ## #",
    "#                 #",
    "# ## # ##### # ## #",
    "#    #   #   #    #",
    "#### ### # ### ####",
    "   # #       # #   ",
    "#### # ## ## # ####",
    "       #   #       ",
    "#### # ##### # ####",
    "   # #       # #   ",
    "#### ### # ### ####",
    "#    #   #   #    #",
    "# ## # ##### # ## #",
    "#                 #",
    "# ## ### # ### ## #",
    "#        #        #",
    "###################"
};
// clang-format on

void PacmanGame::init()
{
    _timer = 0;
    _player = VectorInt(9, 15);
    _player_mov = VectorInt(-1, 0);
    _Blink = VectorInt(9, 9);
    _palette.setColor(0, 'P', YELLOW);
    _palette.setColor(1, 'B', RED);
    _palette.setColor(2, '#', BLUE);
    _palette.setColor(3, 't', WHITE);
}

void PacmanGame::update(float dt [[maybe_unused]])
{
    Event event;
    while (_manager->pollEvent(event)) {

        if (event.type == Event::QUIT) {
            _graphic->close();
        }
        if (event.type == Event::KEYDOWN) {
            if (event.keyboardInput.keyCode == KeyCode::Z
                && this->getCollide(arc::game::VectorInt(0, -1)) == false) {
                _player_mov.setValue(0, -1);
            }
            if (event.keyboardInput.keyCode == KeyCode::S
                && this->getCollide(arc::game::VectorInt(0, 1)) == false) {
                _player_mov.setValue(0, 1);
            }
            if (event.keyboardInput.keyCode == KeyCode::Q
                && this->getCollide(arc::game::VectorInt(-1, 0)) == false) {
                _player_mov.setValue(-1, 0);
            }
            if (event.keyboardInput.keyCode == KeyCode::D
                && this->getCollide(arc::game::VectorInt(1, 0)) == false) {
                _player_mov.setValue(1, 0);
            }
        }
    }
    _timer += dt;
    if (_player.value.x + _player_mov.value.x == -1) {
        _player.value.x = 18;
    }
    if (_player.value.x + _player_mov.value.x >= 19) {
        _player.value.x = 0;
    }
    if (this->getCollide(_player_mov) == true) {
        _player_mov = arc::game::VectorInt(0, 0);
    }
    if (_timer >= 0.50) {
        _player += _player_mov;
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

    _canvas->drawPoint(
        this->_Blink.value.x, this->_Blink.value.y, this->_palette[1]);

    _canvas->drawPoint(
        this->_player.value.x, this->_player.value.y, this->_palette[0]);

    _canvas->drawText(1, 1, "abcdefghijklmnopqrstuvwxyz", this->_palette[1]);
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

void PacmanGame::setManager(IManager* manager) { _manager = manager; }

bool PacmanGame::getCollide(VectorInt nextPos)
{
    if (_player.value.x + nextPos.value.x < 0
        || _player.value.x + nextPos.value.x > 18)
        return (false);
    if (this->_map.at(_player.value.y + nextPos.value.y)
            .at(_player.value.x + nextPos.value.x)
        == '#') {
        return (true);
    }
    return (false);
}

} // namespace arc::game
