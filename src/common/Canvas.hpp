/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** Canavas
*/

#pragma once
#include "spc/graphic/ICanvas.hpp"

namespace arc::grph {

class ACanvas : public ICanvas {
 public:
    ACanvas() = default;
    ~ACanvas() = default;

    CanvasCapacity getCapacities() const override
    {
        return CanvasCapacity::NONE;
    }

    void startDraw() override { }
    void endDraw() override { }

    void drawPoint(int x [[maybe_unused]], int y [[maybe_unused]],
        const IColor& color [[maybe_unused]]) override
    {
    }

    void drawText(int x [[maybe_unused]], int y [[maybe_unused]],
        const std::string& text [[maybe_unused]],
        const IColor& foreColor [[maybe_unused]]) override
    {
    }

    void drawSprite(const game::ISprite& sprite [[maybe_unused]]) override { }
};

}
