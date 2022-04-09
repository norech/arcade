/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** NcursesGraphic
*/

#include "NcursesGraphic.hpp"
#include "NcursesCanvas.hpp"
#include <iostream>

namespace arc::grph {

bool NcursesGraphic::_hasColorsSet = false;

// clang-format off
std::unordered_map<int, arc::KeyCode> NcursesGraphic::_keyMap
    = {
        { '\n', KeyCode::ENTER },
        { KEY_BACKSPACE, KeyCode::BACKSPACE },
        { KEY_UP, KeyCode::Z },
        { KEY_DOWN, KeyCode::S },
        { KEY_LEFT, KeyCode::Q },
        { KEY_RIGHT, KeyCode::D },
        { ' ', KeyCode::SPACE }
    };
// clang-format on

void NcursesGraphic::init()
{
    _window = initscr();
    timeout(25);
    curs_set(0);
    noecho();
    if (has_colors() && !_hasColorsSet) {
        _hasColorsSet = true;
        start_color();
        use_default_colors();
        init_color(COLOR_BLACK, 1, 1, 1);
        init_pair(0, COLOR_BLACK, COLOR_BLACK); // black
        init_pair(1, COLOR_WHITE, COLOR_WHITE); // white
        init_pair(2, COLOR_RED, COLOR_RED); // red
        init_pair(3, COLOR_GREEN, COLOR_GREEN); // green
        init_pair(4, COLOR_BLUE, COLOR_BLUE); // blue
        init_pair(5, COLOR_YELLOW, COLOR_YELLOW); // yellow
        init_pair(6, COLOR_CYAN, COLOR_CYAN); // cyan
        init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA); // magenta
        init_pair(8, COLOR_BLACK, COLOR_BLACK); // black
        init_pair(9, COLOR_WHITE, COLOR_BLACK); // white
        init_pair(10, COLOR_RED, COLOR_BLACK); // red
        init_pair(11, COLOR_GREEN, COLOR_BLACK); // green
        init_pair(12, COLOR_BLUE, COLOR_BLACK); // blue
        init_pair(13, COLOR_YELLOW, COLOR_BLACK); // yellow
        init_pair(14, COLOR_CYAN, COLOR_BLACK); // cyan
        init_pair(15, COLOR_MAGENTA, COLOR_BLACK); // magenta
    }
    keypad(_window, TRUE);
}

bool NcursesGraphic::isOpen()
{
    if (_willBeClosed)
        return false;
    if (_window == nullptr) {
        return false;
    } else {
        return true;
    }
}

void NcursesGraphic::close() { _willBeClosed = true; }

void NcursesGraphic::render() { wrefresh(_window); }

void NcursesGraphic::clear() { wclear(_window); }

bool NcursesGraphic::pollEvent(Event& input)
{
    int key = getch();

    if (key != ERR) {
        for (auto& it : _keyMap) {
            if (it.first == key) {
                input.keyboardInput.keyCode = it.second;
                input.type = Event::EventType::KEYDOWN;
                return true;
            }
        }
        input.keyboardInput.keyCode = key;
        input.type = Event::EventType::KEYDOWN;
        return (true);
    }
    return (false);
}

float NcursesGraphic::tick() { return (0.025); }

void NcursesGraphic::loadCanvas(std::shared_ptr<ICanvas>& canvas)
{
    canvas = std::make_shared<NcursesCanvas>(this);
}

void NcursesGraphic::unloadCanvas(std::shared_ptr<ICanvas>& canvas)
{
    canvas.reset();
}

void NcursesGraphic::destroy()
{
    echo();
    endwin();
}

int NcursesGraphic::getColorIndex(const ColorCode& color)
{
    static std::array<ColorCode, 8> colors
        = { BLACK, WHITE, RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA };

    ColorCode colorCode = color;
    int colorId = 0;

    for (size_t i = 0; i < colors.size(); i++) {
        if (colorCode == colors[i])
            colorId = i;
    }
    return colorId;
}
void NcursesGraphic::registerSprite(game::ISprite& sprite [[maybe_unused]])
{
    return;
}
}
