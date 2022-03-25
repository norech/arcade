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
    _palette.setColor(0, 'P', GREEN);
    _palette.setColor(1, 'W', YELLOW);
    _palette.setColor(2, 'O', RED);
    this->initMap();
    _playerX = 10;
    _playerY = 10;
    _velocityX = 0;
    _velocityY = 0;
    _move = 0;
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
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::S) {
                _playerY++;
                _velocityX = 0;
                _velocityY = 1;
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::Q) {
                _playerX--;
                _velocityX = -1;
                _velocityY = 0;
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::D) {
                _playerX++;
                _velocityX = 1;
                _velocityY = 0;
            }
        }
        std::cout << "vxl = " << _velocityX << " vyl = " << _velocityY << std::endl;
    }
    if (_map.at(_playerY).at(_playerX) == 'O')
        _map.at(_playerY).at(_playerX) = ' ';
    _move++;
    if (_map.at(_playerY).at(_playerX) == '#') {
        _velocityX = 0;
        _velocityY = 0;
        _move = 0;
    }
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
        _move = 0;
    }
}

void arc::game::NibblerGame::collision()
{
    if (_map.at(_playerY).at(_playerX) == '#' && _velocityX == 1)
        _playerX--;
    if (_map.at(_playerY).at(_playerX) == '#' && _velocityX == -1)
        _playerX++;
    if (_map.at(_playerY).at(_playerX) == '#' && _velocityY == 1)
        _playerY--;
    if (_map.at(_playerY).at(_playerX) == '#' && _velocityY == -1)
        _playerY++;
}
