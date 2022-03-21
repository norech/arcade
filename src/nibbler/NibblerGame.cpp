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
    _playerX = 10;
    _playerY = 10;
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
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::S) {
                _playerY++;
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::Q) {
                _playerX--;
            }
            if (event.keyboardInput.keyCode == arc::KeyCode::D) {
                _playerX++;
            }
        }
        if (_map.at(_playerY).at(_playerX) == 'O')
            _map.at(_playerY).at(_playerX) = ' ';
        if (_map.at(_playerY).at(_playerX) == '#' && event.keyboardInput.keyCode == arc::KeyCode::D)
            _playerX--;
        if (_map.at(_playerY).at(_playerX) == '#' && event.keyboardInput.keyCode == arc::KeyCode::Q)
            _playerX++;
        if (_map.at(_playerY).at(_playerX) == '#' && event.keyboardInput.keyCode == arc::KeyCode::S)
            _playerY--;
        if (_map.at(_playerY).at(_playerX) == '#' && event.keyboardInput.keyCode == arc::KeyCode::Z)
            _playerY++;
    }
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
