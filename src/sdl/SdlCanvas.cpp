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

CanvasCapacity SdlCanvas::getCapacities() const
{
    return CanvasCapacity::BASIC;
}

void SdlCanvas::startDraw()
{
    SDL_SetRenderDrawColor(_graphic->renderer, 0, 0, 0, 255);
    SDL_RenderClear(_graphic->renderer);
}

void SdlCanvas::endDraw() { }

void SdlCanvas::drawPoint(int x, int y, const IColor& color)
{
    SDL_Rect rect = { x * 20, y * 20, 20, 20 };

    int r = (color.getColorCode() & 0xFF0000) >> 16;
    int g = (color.getColorCode() & 0x00FF00) >> 8;
    int b = (color.getColorCode() & 0x0000FF);

    SDL_SetRenderDrawColor(_graphic->renderer, r, g, b, 255);
    SDL_RenderFillRect(_graphic->renderer, &rect);
    SDL_RenderDrawRect(_graphic->renderer, &rect);
}

void SdlCanvas::drawText(
    int x, int y, const std::string& text, const IColor& foreColor)
{
    Uint8 r = (foreColor.getColorCode() & 0xFF0000) >> 16;
    Uint8 g = (foreColor.getColorCode() & 0x00FF00) >> 8;
    Uint8 b = (foreColor.getColorCode() & 0x0000FF);

    SDL_Color color = { r, g, b, 255 };
    SDL_Surface* surface
        = TTF_RenderText_Solid(_graphic->font, text.c_str(), color);
    SDL_Texture* texture
        = SDL_CreateTextureFromSurface(_graphic->renderer, surface);
    SDL_Rect trect = { (x * 20) + 3, (y * 20) - 3, 0, 0 };

    SDL_QueryTexture(texture, NULL, NULL, &trect.w, &trect.h);
    SDL_RenderCopy(_graphic->renderer, texture, NULL, &trect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

}
