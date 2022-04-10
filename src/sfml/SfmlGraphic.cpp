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
        { sf::Keyboard::Backspace, arc::KeyCode::BACKSPACE },
        { sf::Keyboard::Up, arc::KeyCode::Z },
        { sf::Keyboard::Down, arc::KeyCode::S },
        { sf::Keyboard::Left, arc::KeyCode::Q },
        { sf::Keyboard::Right, arc::KeyCode::D },
        { sf::Keyboard::Space, arc::KeyCode::SPACE }
    };
// clang-format on

void arc::grph::SfmlGraphic::init()
{
    _shouldClose = false;
    this->window.create(sf::VideoMode(800, 600), "SFML");
    this->window.setFramerateLimit(30);
    this->font.loadFromFile("./font.ttf");
}

bool arc::grph::SfmlGraphic::isOpen()
{
    if (_shouldClose)
        return false;
    if (this->window.isOpen())
        return true;
    else
        return false;
}

void arc::grph::SfmlGraphic::close() { _shouldClose = true; }

void arc::grph::SfmlGraphic::clear() { this->window.clear(); }

void arc::grph::SfmlGraphic::render() { this->window.display(); }

float arc::grph::SfmlGraphic::tick() { return (0.025); }

bool arc::grph::SfmlGraphic::pollEvent(Event& input [[maybe_unused]])
{
    sf::Event sfmlEvent;

    if (!window.pollEvent(sfmlEvent))
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

void arc::grph::SfmlGraphic::destroy() { this->window.close(); };
