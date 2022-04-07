/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** NibblerGame
*/

#include "NibblerGame.hpp"
#include "spc/common/KeyCode.hpp"
#include <iostream>

arc::game::NibblerGame::NibblerGame()
{
}

arc::game::NibblerGame::~NibblerGame()
{
}

void arc::game::NibblerGame::init() {
    std::vector<int> pos;

    _palette.setColor(0, 'P', GREEN);
    _palette.setColor(1, 'W', YELLOW);
    _palette.setColor(2, 'O', MAGENTA);
    this->initMap();
    _velocityX = 0;
    _velocityY = 0;
    _move = 0;
    pos.push_back(10);
    pos.push_back(10);
    _position.push_back(pos);
    _pos_copy.push_back(_position.at(0));
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
                _position.at(0).at(1)--;
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::S) {
                _velocityX = 0;
                _velocityY = 1;
                _position.at(0).at(1)++;
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::Q) {
                _velocityX = -1;
                _velocityY = 0;
                _position.at(0).at(0)--;
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::D) {
                _velocityX = 1;
                _velocityY = 0;
                _position.at(0).at(0)++;
            }
            this->collision();
        }
    }
    this->tailPosition();
    this->eatFood();
    this->movePlayer();
    this->collision();
}

void arc::game::NibblerGame::render() {
    _graphic->clear();
    _canvas->startDraw();

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

void arc::game::NibblerGame::drawMap() {
    for (size_t i = 0; i < _map.size(); i++) {
        for (size_t j = 0; j < _map.at(i).size(); j++) {
            if (_map.at(i).at(j) == '#')
                _canvas->drawPoint(j, i, this->_palette[1]);
            if (_map.at(i).at(j) == 'O')
                _canvas->drawPoint(j, i, this->_palette[2]);
        }
    }
}

void arc::game::NibblerGame::movePlayer()
{
    size_t y = 0;

    if (!this->check_wall(_position.at(0).at(1), _position.at(0).at(0), _map) && _move == 100) {
        _position.at(0).at(0) += _velocityX;
        _position.at(0).at(1) += _velocityY;
        for (size_t i = 1; i < _position.size(); i++) {
            _position.at(i).at(0) = _pos_copy.at(y).at(0);
            _position.at(i).at(1) = _pos_copy.at(y).at(1);
            y++;
        }
        _move = 0;
        y = 0;
    }
    for (size_t i = 0; i < _position.size(); i++) {
        _pos_copy.at(y).at(0) = _position.at(i).at(0);
        _pos_copy.at(y).at(1) = _position.at(i).at(1);
        y++;
    }
    _move++;
}

void arc::game::NibblerGame::collision()
{
    if (_map.at(_position.at(0).at(1)).at(_position.at(0).at(0)) == '#' && _velocityX == 1) {
        _position.at(0).at(0)--;
    }
    if (_map.at(_position.at(0).at(1)).at(_position.at(0).at(0)) == '#' && _velocityX == -1) {
        _position.at(0).at(0)++;
    }
    if (_map.at(_position.at(0).at(1)).at(_position.at(0).at(0)) == '#' && _velocityY == 1) {
        _position.at(0).at(1)--;
    }
    if (_map.at(_position.at(0).at(1)).at(_position.at(0).at(0)) == '#' && _velocityY == -1) {
        _position.at(0).at(1)++;
    }
}

bool arc::game::NibblerGame::check_wall(int x, int y, std::vector<std::string> map)
{
    if (map.at(y - 1).at(x) == '#') {
        std::cout << "left: " << x << " " << y << std::endl;
        return true;
    }
    if (map.at(y + 1).at(x) == '#') {
        std::cout << "right: " << x << " " << y << std::endl;
        return true;
    }
    if (map.at(y).at(x - 1) == '#') {
        std::cout << "up: " << x << " " << y << std::endl;
        return true;
    }
    if (map.at(y).at(x + 1) == '#') {
        std::cout << "down: " << x << " " << y << std::endl;
        return true;
    }
    if (map.at(y).at(x) == '#') {
        std::cout << "middle: " << x << " " << y << std::endl;
        this->collision();
        return true;
    }
    return false;
}

void arc::game::NibblerGame::tailPosition()
{
    std::vector<int> pos;
    size_t size = _position.size() - 1;

    if (_map.at(_position.at(0).at(1)).at(_position.at(0).at(0)) == 'O') {
        pos.push_back(_position.at(size).at(0) - _velocityX);
        pos.push_back(_position.at(size).at(1) - _velocityY);
        _position.push_back(pos);
        _pos_copy.push_back(pos);
    }
}

void arc::game::NibblerGame::drawTail()
{
    for (size_t i = 0; i < _position.size(); i++) {
        _canvas->drawPoint(_position.at(i).at(0), _position.at(i).at(1), this->_palette[0]);
    }
}

void arc::game::NibblerGame::eatFood()
{
    if (_map.at(_position.at(0).at(1)).at(_position.at(0).at(0)) == 'O')
        _map.at(_position.at(0).at(1)).at(_position.at(0).at(0)) = ' ';
}
