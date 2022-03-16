/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** SdlCanvas
*/

#include "SdlCanvas.hpp"

namespace arc::grph {

    SdlCanvas::SdlCanvas(SdlGraphic *graphic)
    {
        _graphic = dynamic_cast<SdlGraphic *>(graphic);

        if (_graphic == nullptr) {
            std::cerr << "error not sfml graphics" << std::endl;
            if (graphic != nullptr) {
                graphic->close();
            } else {
                exit(84);
            }
        }
    }

    SdlCanvas::~SdlCanvas()
    {
    }

    void SdlCanvas::startDraw()
    {

    }

    void SdlCanvas::endDraw()
    {

    }

    void SdlCanvas::drawPoint(int x, int y, const IColor &color)
    {
        SDL_Rect rect = {x * 100, y * 100, 100, 100};
        SDL_Surface *drawSurface = SDL_GetWindowSurface(_graphic->_window);

        SDL_FillRect(drawSurface, &rect, SDL_MapRGB(drawSurface->format, (color.getColorCode() & 0xFF0000) >> 4,
            (color.getColorCode() & 0x00FF00) >> 2, color.getColorCode() & 0x0000FF));
    }
}