/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** SfmlGraphic
*/

#ifndef SFMLGRAPHIC_HPP_
#define SFMLGRAPHIC_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

#include "spc/common/KeyCode.hpp"
#include "spc/graphic/ICanvas.hpp"
#include "spc/graphic/IGraphic.hpp"
#include "../common/Graphic.hpp"

namespace arc::grph {
class SfmlGraphic : public AGraphic {
 public:
    SfmlGraphic() = default;
    ~SfmlGraphic() = default;

    void init() override;
    bool isOpen() override;
    void close() override;
    void render() override;
    float tick() override;
    bool pollEvent(Event& input) override;
    void loadCanvas(std::shared_ptr<ICanvas>& canvas) override;
    void unloadCanvas(std::shared_ptr<ICanvas>& canvas) override;
    void destroy() override;
    void clear() override;
    void registerSprite(game::ISprite& sprite);

    sf::RenderWindow _window;
    sf::Font _font;
    static std::unordered_map<int, arc::KeyCode> _keyMap;

 protected:
 private:
    sf::Event _event;
    bool _shouldClose;
};
}

#endif /* !SFMLGRAPHIC_HPP_ */
