//
// EPITECH PROJECT, 2022
// arcade
// File description:
// graphic
//

#pragma once
#include "spc/graphic/IGraphic.hpp"

namespace arc::grph {

    class graphic : public IGraphic
    {
        public:
            graphic() = default;
            ~graphic() = default;

            void init() override = default;
            void close() override = default;
            void renderer() override = default;


            bool pollEvent(Event &input) override = default;
            bool isOpen() override = default;

            void loadCanvas(std::shared_ptr<ICanvas> &canvas) override = default;
            void unloadCanvas(std::shared_ptr<ICanvas> &canvas) override = default;
            void destroy() override = default;

    };
}
