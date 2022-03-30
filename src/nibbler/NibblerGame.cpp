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
    _palette.setColor(2, 'O', RED);
    this->initMap();
    _playerX = 10;
    _playerY = 10;
    _velocityX = 0;
    _velocityY = 0;
    _move = 0;
    pos.push_back(10);
    pos.push_back(10);
    _position.push_back(pos);
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
                _playerY--;
                _velocityX = 0;
                _velocityY = -1;
                _position.at(0).at(1)--;
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::S) {
                _playerY++;
                _velocityX = 0;
                _velocityY = 1;
                _position.at(0).at(1)++;
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::Q) {
                _playerX--;
                _velocityX = -1;
                _velocityY = 0;
                _position.at(0).at(0)--;
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::D) {
                _playerX++;
                _velocityX = 1;
                _velocityY = 0;
                _position.at(0).at(0)++;
            }
            this->collision();
        }
    }
    if (_map.at(_playerY).at(_playerX) == 'O')
        _map.at(_playerY).at(_playerX) = ' ';
    _move++;
    this->movePlayer();
    this->collision();
}

void arc::game::NibblerGame::render() {
    _graphic->clear();
    _canvas->startDraw();

    this->drawMap();
    _canvas->drawPoint(this->_playerX, this->_playerY, this->_palette[0]);

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

void arc::game::NibblerGame::movePlayer()
{
    if (_map.at(_playerY).at(_playerX) != '#' && _move == 100) {
        _playerX += _velocityX;
        _playerY += _velocityY;
        _position.at(0).at(0) += _velocityX;
        _position.at(0).at(1) += _velocityY;
        _move = 0;
    }
}

void arc::game::NibblerGame::collision()
{
    if (_map.at(_playerY).at(_playerX) == '#' && _velocityX == 1) {
        _playerX--;
        _position.at(0).at(0)--;
    }
    if (_map.at(_playerY).at(_playerX) == '#' && _velocityX == -1) {
        _playerX++;
        _position.at(0).at(0)++;
    }
    if (_map.at(_playerY).at(_playerX) == '#' && _velocityY == 1) {
        _playerY--;
        _position.at(0).at(1)--;
    }
    if (_map.at(_playerY).at(_playerX) == '#' && _velocityY == -1) {
        _playerY++;
        _position.at(0).at(1)++;
    }
}

void arc::game::NibblerGame::tailPosition()
{
    std::vector<int> pos;
    size_t size = _position.size() - 1;

    if (_map.at(_position.at(0).at(1)).at(_position.at(0).at(0)) == 'O') {
        //if (size > 1 && _position.at(size).at(0) == _position.at(size - 1).at(0)) {
        //    pos.push_back(_position.at(size).at(0));
        //    pos.push_back(_position.at(size).at(1) - _velocityY);
        //}
        //if (size > 1 && _position.at(size).at(1) == _position.at(size - 1).at(1)) {
        //    pos.push_back(_position.at(size).at(0) - _velocityX);
        //    pos.push_back(_position.at(size).at(1));
        //}
        //if (size == 1) {
        //    pos.push_back(_position.at(size).at(0) - _velocityX);
        //    pos.push_back(_position.at(size).at(1));
        //}
        pos.push_back(_position.at(size).at(0) - _velocityX);
        pos.push_back(_position.at(size).at(1) - _velocityY);
        _position.push_back(pos);
    }
    std::cout << _position.at(0).at(0) << " " << _position.at(0).at(1) << std::endl;
    for (size_t i = 1; i < _position.size(); i++) {
        _position.at(i).at(0) += _velocityX;
        _position.at(i).at(1) += _velocityY;
        std::cout << _position.at(i).at(0) << " " << _position.at(i).at(1) << std::endl;
    }
}
