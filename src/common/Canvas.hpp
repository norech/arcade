/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** Canavas
*/

#pragma once
#include "spc/graphic/ICanvas.hpp"

namespace arc::grph {

    class Canvas : public ICanvas
    {
        public:
            Canvas() = default;
            ~Canvas() = default;

            void startDraw() override {}
            void endDraw() override {}

            void drawPoint(int x [[maybe_unused]], int y [[maybe_unused]], const IColor &color [[maybe_unused]]) override {}

    };

}
