/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** SdlCanvas
*/

#pragma once

#include "../common/Canvas.hpp"
#include "SdlGraphic.hpp"

namespace arc::grph {

    class SdlCanvas : public Canvas {
        public:
            SdlCanvas(IGraphic *graphic);
            ~SdlCanvas();

            void startDraw() override;

            void endDraw() override;

            void drawpoint(int x, int y, const IColor &color);


        protected:
        private:
            SdlGraphic *_graphic;
    };
}
