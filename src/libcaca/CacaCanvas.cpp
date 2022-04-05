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

CacaCanvas::CacaCanvas(CacaGraphic *graphic)
{
    _graphic = graphic;
}

CacaCanvas::~CacaCanvas()
{
}

void CacaCanvas::startDraw()
{

}

void CacaCanvas::endDraw()
{

}

void CacaCanvas::drawPoint(int x, int y, const IColor &color)
{
    caca_set_color_ansi(_graphic->_canvas, _graphic->getCacaColor(color), CACA_BLACK);
    caca_put_char(_graphic->_canvas, x, y, color.getSymbol());
}
}
