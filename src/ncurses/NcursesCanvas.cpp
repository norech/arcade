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

NcursesCanvas::NcursesCanvas(NcursesGraphic* graphic) { _graphic = graphic; }

NcursesCanvas::~NcursesCanvas() { }

void NcursesCanvas::startDraw() { }

void NcursesCanvas::endDraw() { }

CanvasCapacity NcursesCanvas::getCapacities() const
{
    return CanvasCapacity::BASIC;
}

void NcursesCanvas::drawPoint(int x, int y, const IColor& color)
{
    int colorId = _graphic->getColorIndex(color.getColorCode());

    attron(COLOR_PAIR(colorId));
    mvaddch(y, x * 2, color.getSymbol());
    mvaddch(y, x * 2 + 1, ' ');
    attroff(COLOR_PAIR(colorId));
}
}
