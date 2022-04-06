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

void NcursesCanvas::drawText(
    int x, int y, const std::string& text, const IColor& color [[maybe_unused]])
{
    int colorId = _graphic->getColorIndex(color.getColorCode()) + 8;

    attron(COLOR_PAIR(colorId));
    mvprintw(y, x * 2, "%s", text.c_str());
    attroff(COLOR_PAIR(colorId));
}
}
