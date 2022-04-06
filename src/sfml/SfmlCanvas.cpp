/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** SfmlCanvas
*/

#include "SfmlCanvas.hpp"

arc::grph::SfmlCanvas::SfmlCanvas(SfmlGraphic* graphic)
{
    this->_graphic = graphic;
}

arc::grph::SfmlCanvas::~SfmlCanvas() { }

arc::grph::CanvasCapacity arc::grph::SfmlCanvas::getCapacities() const
{
    return arc::grph::CanvasCapacity::BASIC;
}

void arc::grph::SfmlCanvas::startDraw() { }

void arc::grph::SfmlCanvas::endDraw() { }

void arc::grph::SfmlCanvas::drawPoint(int x, int y, const IColor& color)
{
    int r = (color.getColorCode() & 0xFF0000) >> 16;
    int g = (color.getColorCode() & 0x00FF00) >> 8;
    int b = (color.getColorCode() & 0x0000FF);

    sf::RectangleShape rectangle(sf::Vector2f(20, 20));
    rectangle.setFillColor(sf::Color(r, g, b, 255));
    rectangle.setPosition(x * 20, y * 20);
    this->_graphic->_window.draw(rectangle);
}

void arc::grph::SfmlCanvas::drawText(
    int x, int y, const std::string& text, const IColor& color)
{
    sf::Text toDraw(text, _graphic->_font, 20);
    toDraw.setFillColor(sf::Color((color.getColorCode() << 8) + 0xFF));
    toDraw.setPosition((x * 20) + 3, (y * 20) - 3);
    toDraw.setLetterSpacing(1);
    this->_graphic->_window.draw(toDraw);
}
