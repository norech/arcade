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
    Vector2 pos;

    _palette.setColor(0, 'P', GREEN);
    _palette.setColor(1, 'W', YELLOW);
    _palette.setColor(2, 'O', RED);
    this->initMap();
    _velocityX = 0;
    _velocityY = 0;
    _move = 0;
    pos.x = 10;
    pos.y = 10;
    _position.push_back(pos);
    _pos_copy.push_back(_position.at(0));
};

void arc::game::NibblerGame::update(float dt [[maybe_unused]]) {
    Event event;
    while (_manager->pollEvent(event)) {

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

    _canvas->drawText(1, 23, "Score:", this->_palette[1]);
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
    //int px = _position.at(0).x;
    //int py = _position.at(0).y;
    size_t y = 0;
    bool wall = this->check_wall(_position.at(0).x, _position.at(0).y, _map);

    //std::cout << "wall: " << wall << std::endl;
    //if (_map.at(py).at(px) != '#' && _move == 10) {
    if (wall == false && _move == 10) {
        _position.at(0).x += _velocityX;
        _position.at(0).y += _velocityY;
        for (size_t i = 1; i < _position.size(); i++) {
            _position.at(i).x = _pos_copy.at(y).x;
            _position.at(i).y = _pos_copy.at(y).y;
            y++;
        }
        _move = 0;
        y = 0;
    }
    for (size_t i = 0; i < _position.size(); i++) {
        _pos_copy.at(y).x = _position.at(i).x;
        _pos_copy.at(y).y = _position.at(i).y;
        y++;
    }
    _move++;
}

void arc::game::NibblerGame::collision()
{
    if (_map.at(_position.at(0).y).at(_position.at(0).x) == '#' && _velocityX == 1) {
        //std::cout << "right" << std::endl;
        _position.at(0).x--;
    }
    if (_map.at(_position.at(0).y).at(_position.at(0).x) == '#' && _velocityX == -1) {
        //std::cout << "left" << std::endl;
        _position.at(0).x++;

    }
    if (_map.at(_position.at(0).y).at(_position.at(0).x) == '#' && _velocityY == 1) {
        //std::cout << "down" << std::endl;
        _position.at(0).y--;
    }
    if (_map.at(_position.at(0).y).at(_position.at(0).x) == '#' && _velocityY == -1) {
        //std::cout << "up" << std::endl;
        _position.at(0).y++;
    }
}

bool arc::game::NibblerGame::check_wall(int x, int y, std::vector<std::string> map)
{
    //std::cout << "move: " << _velocityX << " " << _velocityY << std::endl;
    if (map.at(y).at(x) == '#') {
        //std::cout << "middle: " << x << " " << y << std::endl;
        return true;
    }
    if (map.at(y - 1).at(x) == '#' && _velocityY == -1) {
        //std::cout << "up: " << x << " " << y << std::endl;
        return true;
    }
    if (map.at(y + 1).at(x) == '#' && _velocityY == 1) {
        //std::cout << "down: " << x << " " << y << std::endl;
        return true;
    }
    if (map.at(y).at(x - 1) == '#' && _velocityX == -1) {
        //std::cout << "left: " << x << " " << y << std::endl;
        return true;
    }
    if (map.at(y).at(x + 1) == '#' && _velocityX == 1) {
        //std::cout << "right: " << x << " " << y << std::endl;
        return true;
    }
    return false;
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
        _canvas->drawPoint(_position.at(i).x, _position.at(i).y, this->_palette[0]);
    }
}

void arc::game::NibblerGame::eatFood()
{
    if (_map.at(_position.at(0).y).at(_position.at(0).x) == 'O')
        _map.at(_position.at(0).y).at(_position.at(0).x) = ' ';
}
