/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** NcursesCanvas
*/

#include "NcursesCanvas.hpp"
#include "NcursesGraphic.hpp"
#include <iostream>

namespace arc::grph {

    NcursesCanvas::NcursesCanvas(NcursesGraphic* graphic)
    {
        _graphic = graphic;
    }

    NcursesCanvas::~NcursesCanvas()
    {

    }

    void NcursesCanvas::startDraw()
    {

    }

    void NcursesCanvas::endDraw()
    {

    }

    void NcursesCanvas::drawPoint(int x, int y, const IColor &color)
    {
        std::cout << "here" << std::flush;
        mvaddch(y + 1, x + 1, color.getSymbol());
    }
}