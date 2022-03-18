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

    NcursesGraphic::NcursesGraphic(std::string &name [[maybe_unused]], int x [[maybe_unused]], int y [[maybe_unused]])
    {
        
    }

    NcursesGraphic::~NcursesGraphic()
    {
    }

    void NcursesGraphic::init()
    {
        _window = initscr();
        timeout(25);
        curs_set(0);
        noecho();
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

    void NcursesGraphic::render()
    {
        refresh();
    }

    void NcursesGraphic::clear()
    {
        wclear(_window);
    }

    bool NcursesGraphic::pollEvent(Event &input)
    {
        int key = getch();

        if (key != ERR) {
            input.type = Event::EventType::KEYDOWN;
            input.keyboardInput.keyCode = key;
            return (true);
        }
        return (false);
    }

    float NcursesGraphic::tick()
    {
        return (0);
    }

    void NcursesGraphic::loadCanvas(std::shared_ptr<ICanvas> &canvas)
    {
        canvas = std::make_shared<NcursesCanvas>(this);
    }

    void NcursesGraphic::unloadCanvas(std::shared_ptr<ICanvas> &canvas)
    {
        canvas.reset();
    }

    void NcursesGraphic::destroy()
    {

    }

}
