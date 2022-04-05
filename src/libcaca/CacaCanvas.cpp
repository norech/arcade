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
    caca_set_color_argb(_graphic->_canvas, CACA_BLACK, color.getColorCode() + 0xFF000000);
    caca_put_char(_graphic->_canvas, x, y, color.getSymbol());
}
}
