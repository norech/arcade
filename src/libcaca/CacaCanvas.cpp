//
// EPITECH PROJECT, 2022
// arcade
// File description:
// canvas
//

#include "CacaCanvas.hpp"
#include "CacaGraphic.hpp"
#include <iostream>

namespace arc::grph {

CacaCanvas::CacaCanvas(CacaGraphic* graphic) { _graphic = graphic; }

CacaCanvas::~CacaCanvas() { }

void CacaCanvas::startDraw() { }

void CacaCanvas::endDraw() { }

void CacaCanvas::drawPoint(int x, int y, const IColor& color)
{
    caca_set_color_ansi(
        _graphic->canvas, _graphic->getCacaColor(color), CACA_BLACK);
    caca_printf(_graphic->canvas, x, y, "%c", color.getSymbol());
}

void CacaCanvas::drawText(
    int x, int y, const std::string& text, const IColor& color)
{
    caca_set_color_ansi(
        _graphic->canvas, _graphic->getCacaColor(color), CACA_BLACK);
    caca_printf(_graphic->canvas, x, y, "%s", text.c_str());
}
}
