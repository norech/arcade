/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** NcursesCanvas
*/

#pragma once

#include "../common/Canvas.hpp"
#include "ncurses.h"
#include "NcursesGraphic.hpp"

namespace arc::grph {

    class NcursesCanvas : public Canvas {
        public:
            NcursesCanvas(NcursesGraphic *graphic);
            ~NcursesCanvas();


            void startDraw() override;
            void endDraw() override;
            void drawPoint(int x, int y, const IColor &color);
        private:
            NcursesGraphic *_graphic;
    };  
}