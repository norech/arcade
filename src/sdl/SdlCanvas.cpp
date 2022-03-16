/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** SdlCanvas
*/

#include "SdlCanvas.hpp"

namespace arc::grph {

    SdlCanvas::SdlCanvas(IGraphic *graphic)
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

    void SdlCanvas::drawpoint(int x, int y, const IColor &color)
    {
        SDL_Rect rect = {x * 100, y * 100, 100, 100};
        SDL_Surface *drawSurface = SDL_GetWindowSurface(_graphic->_window);

    }
}