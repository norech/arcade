/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** SfmlGraphic
*/

#include "SfmlGraphic.hpp"
#include "SfmlCanvas.hpp"
#include <unordered_map>

// clang-format off
std::unordered_map<int, arc::KeyCode> arc::grph::SfmlGraphic::_keyMap
    = {
        { sf::Keyboard::Return, arc::KeyCode::ENTER },
        { sf::Keyboard::Backspace, arc::KeyCode::ESCAPE },
        { sf::Keyboard::Up, arc::KeyCode::Z },
        { sf::Keyboard::Down, arc::KeyCode::Q },
        { sf::Keyboard::Left, arc::KeyCode::S },
        { sf::Keyboard::Right, arc::KeyCode::D },
        { sf::Keyboard::Space, arc::KeyCode::SPACE }
    };
// clang-format on

void arc::grph::SfmlGraphic::init()
{
    _shouldClose = false;
    this->_window.create(sf::VideoMode(800, 600), "SFML");
    this->_window.setFramerateLimit(30);
    this->_font.loadFromFile("./font.ttf");
}

bool arc::grph::SfmlGraphic::isOpen()
{
    if (_shouldClose)
        return false;
    if (this->_window.isOpen())
        return true;
    else
        return false;
}

void arc::grph::SfmlGraphic::close() { _shouldClose = true; }

void arc::grph::SfmlGraphic::clear() { this->_window.clear(); }

void arc::grph::SfmlGraphic::render() { this->_window.display(); }

float arc::grph::SfmlGraphic::tick() { return (0.025); }

bool arc::grph::SfmlGraphic::pollEvent(Event& input [[maybe_unused]])
{
    sf::Event sfmlEvent;

    if (!_window.pollEvent(sfmlEvent))
        return false;
    if (sfmlEvent.type == sf::Event::Closed) {
        input.type = Event::QUIT;
        return true;
    }
    if (sfmlEvent.type == sf::Event::KeyPressed) {
        input.type = Event::KEYDOWN;
        for (auto& it : _keyMap) {
            if (it.first == sfmlEvent.key.code) {
                input.keyboardInput.keyCode = it.second;
                return true;
            }
        }
        if (sfmlEvent.key.code < sf::Keyboard::A
            || sfmlEvent.key.code > sf::Keyboard::Z) {
            return false;
        }
        input.type = Event::KEYDOWN;
        input.keyboardInput.keyCode
            = (sfmlEvent.key.code - sf::Keyboard::A) + arc::KeyCode::A;
        return true;
    }
    return false;
}

void arc::grph::SfmlGraphic::loadCanvas(
    std::shared_ptr<ICanvas>& canvas [[maybe_unused]])
{
    canvas = std::make_shared<SfmlCanvas>(this);
};

void arc::grph::SfmlGraphic::unloadCanvas(
    std::shared_ptr<ICanvas>& canvas [[maybe_unused]])
{
    canvas.reset();
};

void arc::grph::SfmlGraphic::destroy() { this->_window.close(); };

void arc::grph::SfmlGraphic::registerSprite(
    game::ISprite& sprite [[maybe_unused]])
{
    return;
}
