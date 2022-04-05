//
// EPITECH PROJECT, 2022
// arcade
// File description:
// libcaca
//

#pragma once

#include <caca.h>
#include "../common/Canvas.hpp"
#include "CacaGraphic.hpp"

namespace arc::grph {
    class CacaCanvas : public Canvas {
        public:
            CacaCanvas(CacaGraphic *graphic);
            ~CacaCanvas();

            void startDraw() override;
            void endDraw() override;
            void drawPoint(int x, int y, const IColor& color);
            void drawText(int x, int y, const std::string &text, const IColor &color);
        private:
            CacaGraphic *_graphic;
    };
};

