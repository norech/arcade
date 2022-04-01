/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** SfmlCanvas
*/

#ifndef SFMLCANVAS_HPP_
#define SFMLCANVAS_HPP_

#include <SFML/Graphics.hpp>

#include "../common/Canvas.hpp"
#include "SfmlGraphic.hpp"

namespace arc::grph {
class SfmlCanvas : public Canvas {
 public:
    SfmlCanvas(SfmlGraphic* graphic);
    ~SfmlCanvas();

    CanvasCapacity getCapacities() const override;
    void startDraw() override;
    void endDraw() override;
    void drawPoint(int x, int y, const IColor& color) override;

 protected:
 private:
    SfmlGraphic* _graphic;
};
}

#endif /* !SFMLCANVAS_HPP_ */
