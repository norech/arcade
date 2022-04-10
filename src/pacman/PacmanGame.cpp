
#include "spc/common/KeyCode.hpp"
#include <iostream>
#include "../common/VectorInt.hpp"
#include "PacmanGame.hpp"
#include <stack>

namespace arc::game {

// clang-format off
std::vector<std::string> PacmanGame::_map = {
    "#######################",
    "#oooooooooo#oooooooooo#",
    "#O###o####o#o####o###O#",
    "#ooooooooooooooooooooo#",
    "#o###o#o#######o#o###o#",
    "#ooooo#oooo#oooo#ooooo#",
    "#####o####o#o####o#####",
    "    #o#         #o#    ",
    "    #o# ####### #o#    ",
    "#####o# #     # #o#####",
    "    Go  #     #  oG    ",
    "#####o# #     # #o#####",
    "    #o# ####### #o#    ",
    "    #o#         #o#    ",
    "#####o# ####### #o#####",
    "#oooooooooo#oooooooooo#",
    "#o###o####o#o####o###o#",
    "#Ooo#oooooo oooooo#ooO#",
    "###o#o#o#######o#o#o###",
    "#ooooo#oooo#oooo#ooooo#",
    "#o########o#o########o#",
    "#oooooooooo#oooooooooo#",
    "#######################"
};
// clang-format on

void PacmanGame::init()
{
    _timer = 0;
    _player = VectorInt(11, 17);
    _player_mov = VectorInt(-1, 0);
    _Blink = VectorInt(11, 7);
    _palette.setColor(0, 'P', YELLOW);
    _palette.setColor(1, 'B', RED);
    _palette.setColor(2, '#', BLUE);
    _palette.setColor(3, 't', WHITE);
    _palette.setColor(4, '#', WHITE);
    _score  = 0;
    _mapCpy = _map;
    _playername = _manager->getPlayerName();
    _highscore = _manager->getHighScore("pacman");
    _pcCount = 100;
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
            if (event.keyboardInput.keyCode == KeyCode::R) {
                hardReset();
                if (_score > _highscore) {
                    _highscore = _score;
                    _manager->setHighScore("pacman", _highscore);
                }
            }
        }
    }
    _timer += dt;
    if (_player.value.x + _player_mov.value.x == -1) {
        _player.value.x = 23;
    }
    if (_player.value.x + _player_mov.value.x >= 23) {
        _player.value.x = 0;
    }
    if (this->getCollide(_player_mov) == true) {
        _player_mov = arc::game::VectorInt(0, 0);
    }
    if (_timer >= 0.50) {
        _player += _player_mov;
        eat(_player);
        _timer = 0;
        blinky();
    }
    if (_pcCount == 0) {
        _score += 1000;
        reset();
    }
}

bool PacmanGame::mustLoadAnotherGraphic() const
{
    return this->_mustLoadAnotherGraphic;
}

void PacmanGame::render()
{
    char test[2] = {' ', '\0'};
    _graphic->clear();
    _canvas->startDraw();

    _pcCount = 0;
    for (size_t y = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map.at(y).size(); x++) {
            if (_mapCpy.at(y).at(x) == '#') {
                _canvas->drawPoint(x, y, this->_palette[2]);
            } else if (_mapCpy.at(y).at(x) == 'O' || _map.at(y).at(x) == 'o') {
                test[0] = _mapCpy.at(y).at(x);
                _canvas->drawText(x, y, test, this->_palette[3]);
                _pcCount++;
            }
        }
    }

    _canvas->drawPoint(
        this->_Blink.value.x, this->_Blink.value.y, this->_palette[1]);

    _canvas->drawPoint(this->_player.value.x, this->_player.value.y, this->_palette[0]);
    printScore();


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

void PacmanGame::destroy() {
    if (_score > _highscore) {
        _highscore = _score;
        _manager->setHighScore("pacman", _highscore);
    }
}

void PacmanGame::setManager(IManager* manager) { _manager = manager; }

bool PacmanGame::getCollide(VectorInt nextPos)
{
    if (_player.value.x + nextPos.value.x < 0 || _player.value.x + nextPos.value.x > 22)

        return (false);
    if (this->_map.at(_player.value.y + nextPos.value.y)
            .at(_player.value.x + nextPos.value.x)
        == '#') {
        return (true);
    }
    return (false);
}

void PacmanGame::eat(const VectorInt &vec)
{
    if (_mapCpy.at(vec.value.y).at(vec.value.x) == 'o') {
        _mapCpy.at(vec.value.y).at(vec.value.x) = ' ';
        _score += 1;
    }
    if (_mapCpy.at(vec.value.y).at(vec.value.x) == 'O') {
        _mapCpy.at(vec.value.y).at(vec.value.x) = ' ';
        _score += 10;
    }
}

void PacmanGame::blinky(void)
{
    std::stack<VectorInt> path;
    int x = 0;

    path.push(this->_Blink);
    while (path.top().value.x != _player.value.x && path.top().value.y != _player.value.y) {
        if (x == 5) {
            break;
        }
        if (path.top().value.x > 21) {
            break;
        }
        if (path.top().value.x < 1) {
            break;
        }
        if ((_map.at(path.top().value.y).at(path.top().value.x + 1) != 'G') && (_map.at(path.top().value.y).at(path.top().value.x + 1) != '#') && (path.top().value.x + 1 != path.top().value.x)) {
            path.push(VectorInt(path.top().value.x + 1, path.top().value.y ));
        } else if ((_map.at(path.top().value.y + 1).at(path.top().value.x) != 'G') && (_map.at(path.top().value.y + 1).at(path.top().value.x) != '#') && (path.top().value.y + 1 != path.top().value.y)) {
            path.push(VectorInt(path.top().value.x, path.top().value.y + 1 ));
        } else if ((_map.at(path.top().value.y).at(path.top().value.x - 1) != '#') && (_map.at(path.top().value.y).at(path.top().value.x - 1) != '#') && (path.top().value.x - 1 != path.top().value.x)) {
            path.push(VectorInt(path.top().value.x + -1, path.top().value.y ));
        } else if ((_map.at(path.top().value.y - 1).at(path.top().value.x) != '#') && (_map.at(path.top().value.y - 1).at(path.top().value.x) != '#') && (path.top().value.y - 1 != path.top().value.y)) {
            path.push(VectorInt(path.top().value.x, path.top().value.y + -1 ));
        } else {
            break;
        }
        x++;
    }
    while(path.size() > 2) {
        path.pop();
    }
    _Blink = path.top();
}

void PacmanGame::reset(void)
{
    _mapCpy = _map;
    this->_player = VectorInt(11, 17);
    this->_player_mov = VectorInt(-1, 0);
    if (_score > _highscore) {
        _highscore = _score;
        _manager->setHighScore("pacman", _highscore);
    }
    //this->_Blink = VectorInt(9, 9);
}

void PacmanGame::hardReset(void)
{
    reset();
    this->_score = 0;
}

void PacmanGame::printScore(void)
{
    for (size_t i = 0; i <= 16; i++) {
        _canvas->drawPoint(_map.at(0).size() + i, 0, _palette[4]);
    }
    for (size_t z = 1; z < _map.at(0).size(); z++) {
        _canvas->drawPoint(_map.at(0).size(), z, _palette[4]);
        _canvas->drawPoint(_map.at(0).size() + 16, z, _palette[4]);
    }
    for (size_t i = 0; i <= 16; i++) {
        _canvas->drawPoint(_map.at(0).size() + i, _map.size()-1, _palette[4]);
    }
    _canvas->drawText(_map.at(0).size() + 1, 1, "SCORE:", _palette[4]);
    _canvas->drawText(_map.at(0).size() + 1, 2, std::to_string(this->_score), _palette[4]);
    _canvas->drawText(_map.at(0).size() + 1, 4, "HI-SCORE:", _palette[4]);
    _canvas->drawText(_map.at(0).size() + 1, 5, this->_playername, _palette[4]);
    _canvas->drawText(_map.at(0).size() + 1, 6, std::to_string(this->_highscore), _palette[4]);
}

} // namespace arc::game
