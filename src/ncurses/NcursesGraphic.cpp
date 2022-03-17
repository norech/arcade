/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** NcursesGraphic
*/

#include "NcursesGraphic.hpp"
#include "NcursesCanvas.hpp"

namespace arc::grph {

    NcursesGraphic::NcursesGraphic(std::string &name [[maybe_unused]], int x [[maybe_unused]], int y [[maybe_unused]])
    {
        
    }

    NcursesGraphic::~NcursesGraphic()
    {
    }

    void NcursesGraphic::init()
    {
        _window = newwin(0, 0, 800, 600);
        _window = initscr();
        timeout(500);
        curs_set(0);
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
        endwin();
    }

    void NcursesGraphic::render()
    {
        refresh();
    }

    void NcursesGraphic::clear()
    {
        clear();
    }

    bool NcursesGraphic::pollEvent(Event &input)
    {
        int key = getch();

        if (key != '\0') {
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
