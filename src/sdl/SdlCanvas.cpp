/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** SdlCanvas
*/

#include "SdlCanvas.hpp"
#include <SDL2/SDL_render.h>

namespace arc::grph {

SdlCanvas::SdlCanvas(SdlGraphic* graphic) { _graphic = graphic; }

SdlCanvas::~SdlCanvas() { }

void SdlCanvas::startDraw()
{
    SDL_SetRenderDrawColor(_graphic->_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_graphic->_renderer);
}

void SdlCanvas::endDraw() { }

void SdlCanvas::drawPoint(int x, int y, const IColor& color)
{
    SDL_Rect rect = { x * 100, y * 100, 100, 100 };

    int r = (color.getColorCode() & 0xFF0000) >> 16;
    int g = (color.getColorCode() & 0x00FF00) >> 8;
    int b = (color.getColorCode() & 0x0000FF);

    SDL_SetRenderDrawColor(_graphic->_renderer, r, g, b, 255);
    SDL_RenderFillRect(_graphic->_renderer, &rect);
    SDL_RenderDrawRect(_graphic->_renderer, &rect);
}

}
