/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** NibblerGame
*/

#include "NibblerGame.hpp"
#include "spc/common/KeyCode.hpp"
#include <iostream>
#include <string>

arc::game::NibblerGame::NibblerGame()
{
}

arc::game::NibblerGame::~NibblerGame()
{
}

void arc::game::NibblerGame::init() {
    _palette.setColor(0, 'P', GREEN);
    _palette.setColor(1, 'P', MAGENTA);
    _palette.setColor(2, 'W', YELLOW);
    _palette.setColor(3, 'O', RED);
    this->initMap();
    this->initPlayer();
    _velocityX = 0;
    _velocityY = 0;
    _move = 0;
    _score = 0;
};

void arc::game::NibblerGame::update(float dt [[maybe_unused]]) {
    Event event;
    while (_graphic->pollEvent(event)) {

        if (event.type == Event::QUIT) {
            _graphic->close();
        }

        if (event.type == Event::KEYDOWN) {
            if (event.keyboardInput.keyCode == arc::KeyCode::P)
                _mustLoadAnotherGraphic = true;
            if (event.keyboardInput.keyCode == arc::KeyCode::Z) {
                _velocityX = 0;
                _velocityY = -1;
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::S) {
                _velocityX = 0;
                _velocityY = 1;
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::Q) {
                _velocityX = -1;
                _velocityY = 0;
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::D) {
                _velocityX = 1;
                _velocityY = 0;
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::R) {
                this->reset();
            }
        }
    }
    _move += dt;
    if (_move >= 0.25) {
        this->tailPosition();
        this->eatFood();
        this->movePlayer();
        this->collision();
        _move = 0;
    }
}

void arc::game::NibblerGame::render() {
    _graphic->clear();
    _canvas->startDraw();

    _canvas->drawText(1, 23, "Score: " + std::to_string(_score), this->_palette[2]);
    this->drawMap();
    this->drawTail();

    _canvas->endDraw();
    _graphic->render();
}

void arc::game::NibblerGame::loadGraphic(grph::IGraphic* graphic) {
    this->_mustLoadAnotherGraphic = false;
    _graphic = graphic;
    _graphic->loadCanvas(_canvas);
}

void arc::game::NibblerGame::unloadGraphic() {
    this->_graphic->unloadCanvas(_canvas);
}

bool arc::game::NibblerGame::mustLoadAnotherGraphic() const {
    return this->_mustLoadAnotherGraphic;
};

void arc::game::NibblerGame::setManager(IManager* manager)
{
    _manager = manager;
}

void arc::game::NibblerGame::destroy() {}

void arc::game::NibblerGame::initMap()
{
    _map.push_back("########################################");
    _map.push_back("#                                      #");
    _map.push_back("#    O         ######       ######     #");
    _map.push_back("#                  #    O          O   #");
    _map.push_back("#                  #                   #");
    _map.push_back("#                                      #");
    _map.push_back("#          O              O            #");
    _map.push_back("#                                      #");
    _map.push_back("#           ################           #");
    _map.push_back("#     O                                #");
    _map.push_back("#           ################           #");
    _map.push_back("#                                O     #");
    _map.push_back("#          O                           #");
    _map.push_back("#       #                              #");
    _map.push_back("#       #         #                    #");
    _map.push_back("#       #         #      O          O  #");
    _map.push_back("#       #    O     #                   #");
    _map.push_back("#   O    #          ## ###########     #");
    _map.push_back("#                                      #");
    _map.push_back("########################################");
}

void arc::game::NibblerGame::initPlayer()
{
    Vector2 pos;

    pos.x = 10;
    pos.y = 10;
    for (int i = 0; i < 4; i++) {
        _position.push_back(pos);
        _pos_copy.push_back(_position.at(0));
        pos.x--;
    }
}

void arc::game::NibblerGame::drawMap() {
    for (size_t i = 0; i < _map.size(); i++) {
        for (size_t j = 0; j < _map.at(i).size(); j++) {
            if (_map.at(i).at(j) == '#')
                _canvas->drawPoint(j, i, this->_palette[2]);
            if (_map.at(i).at(j) == 'O')
                _canvas->drawPoint(j, i, this->_palette[3]);
        }
    }
}

void arc::game::NibblerGame::movePlayer()
{
    size_t y = 0;
    bool wall = this->check_wall(_position.at(0).x + _velocityX, _position.at(0).y + _velocityY, _map);

    if (wall == false) {
        _position.at(0).x += _velocityX;
        _position.at(0).y += _velocityY;
        for (size_t i = 1; i < _position.size(); i++) {
            _position.at(i).x = _pos_copy.at(y).x;
            _position.at(i).y = _pos_copy.at(y).y;
            y++;
        }
        y = 0;
    }
    for (size_t i = 0; i < _position.size(); i++) {
        _pos_copy.at(y).x = _position.at(i).x;
        _pos_copy.at(y).y = _position.at(i).y;
        y++;
    }
}

void arc::game::NibblerGame::collision()
{
    if (_map.at(_position.at(0).y).at(_position.at(0).x) == '#' && _velocityX == 1) {
        _position.at(0).x--;
    }
    if (_map.at(_position.at(0).y).at(_position.at(0).x) == '#' && _velocityX == -1) {
        _position.at(0).x++;

    }
    if (_map.at(_position.at(0).y).at(_position.at(0).x) == '#' && _velocityY == 1) {
        _position.at(0).y--;
    }
    if (_map.at(_position.at(0).y).at(_position.at(0).x) == '#' && _velocityY == -1) {
        _position.at(0).y++;
    }
}

bool arc::game::NibblerGame::check_wall(int x, int y, std::vector<std::string> map)
{
    bool ret = false;

    if (map.at(y).at(x) == '#' && _velocityY == -1) {
        ret = true;
    }
    if (map.at(y).at(x) == '#' && _velocityY == 1) {
        ret = true;
    }
    if (map.at(y).at(x) == '#' && _velocityX == -1) {
        ret = true;
    }
    if (map.at(y).at(x) == '#' && _velocityX == 1) {
        ret = true;
    }
    if (_velocityX == 0 && _velocityY == 0) {
        ret = true;
    }
    return ret;
}

void arc::game::NibblerGame::tailPosition()
{
    Vector2 pos;
    size_t size = _position.size() - 1;

    if (_map.at(_position.at(0).y).at(_position.at(0).x) == 'O') {
        pos.x = _position.at(size).x - _velocityX;
        pos.y = _position.at(size).y - _velocityY;
        _position.push_back(pos);
        _pos_copy.push_back(pos);
    }
}

void arc::game::NibblerGame::drawTail()
{
    for (size_t i = 0; i < _position.size(); i++) {
        if (i == 0)
            _canvas->drawPoint(_position.at(i).x, _position.at(i).y, this->_palette[1]);
        else
            _canvas->drawPoint(_position.at(i).x, _position.at(i).y, this->_palette[0]);
    }
}

void arc::game::NibblerGame::eatFood()
{
    if (_map.at(_position.at(0).y).at(_position.at(0).x) == 'O') {
        _map.at(_position.at(0).y).at(_position.at(0).x) = ' ';
        _score += 10;
    }
}

void arc::game::NibblerGame::reset()
{
    for (size_t i = _position.size(); i > 0; i--)
        _position.pop_back();
    for (size_t i = _pos_copy.size(); i > 0; i--)
        _pos_copy.pop_back();
    for (size_t i = _map.size(); i > 0; i--)
        _map.pop_back();
    this->init();
}
