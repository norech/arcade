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
    SdlCanvas(SdlGraphic* graphic);
    ~SdlCanvas();

    CanvasCapacity getCapacities() const override;

    void startDraw() override;

    void endDraw() override;

    void drawPoint(int x, int y, const IColor& color) override;

    void drawText(int x, int y, const std::string &text, const IColor &ForeColor) override;

 protected:
 private:
    SdlGraphic* _graphic;
};
}
