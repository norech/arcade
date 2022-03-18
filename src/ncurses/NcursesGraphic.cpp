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

NcursesGraphic::NcursesGraphic() { }

NcursesGraphic::~NcursesGraphic() { }

void NcursesGraphic::init()
{
    _window = initscr();
    timeout(25);
    curs_set(0);
    noecho();
    if (has_colors()) {
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
    }
}

bool NcursesGraphic::isOpen()
{
    if (_window == nullptr) {
        return false;
    } else {
        return true;
    }
}

void NcursesGraphic::close()
{
    echo();
    endwin();
}

void NcursesGraphic::render() { refresh(); }

void NcursesGraphic::clear()
{
    int backgroundColor = getColorIndex(ColorCode::RED);
    wclear(_window);

    attron(COLOR_PAIR(backgroundColor));
    for (int i = 0; i < 600 / 20; i++) {
        mvprintw(i, 0, std::string(800 / 20 * 2, ' ').c_str());
    }
    attroff(COLOR_PAIR(backgroundColor));
}

bool NcursesGraphic::pollEvent(Event& input)
{
    int key = getch();

    if (key != ERR) {
        input.type = Event::EventType::KEYDOWN;
        input.keyboardInput.keyCode = key;
        return (true);
    }
    return (false);
}

float NcursesGraphic::tick() { return (0); }

void NcursesGraphic::loadCanvas(std::shared_ptr<ICanvas>& canvas)
{
    canvas = std::make_shared<NcursesCanvas>(this);
}

void NcursesGraphic::unloadCanvas(std::shared_ptr<ICanvas>& canvas)
{
    canvas.reset();
}

void NcursesGraphic::destroy() { this->close(); }

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
}
