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

#include "spc/graphic/IGraphic.hpp"
#include "spc/graphic/ICanvas.hpp"

namespace arc::grph {
    class SfmlGraphic : public IGraphic {
        public:
            SfmlGraphic();
            ~SfmlGraphic();

            void init() override;
            bool isOpen() override;
            void close() override;
            void render() override;
            float tick() override;
            bool pollEvent(Event& input) override;
            void loadCanvas(std::shared_ptr<ICanvas>& canvas) override;
            void unloadCanvas(std::shared_ptr<ICanvas>& canvas) override;
            void destroy() override;

            sf::RenderWindow _window;
        protected:
        private:
            sf::Event _event;
    };
}

#endif /* !SFMLGRAPHIC_HPP_ */
