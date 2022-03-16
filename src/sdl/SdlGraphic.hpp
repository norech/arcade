#pragma once

#include "spc/graphic/IGraphic.hpp"
#include "../common/graphic.hpp"
#include <SDL2/SDL.h>
#include <iostream>

namespace arc::grph {

    class SdlGraphic : public Graphic
    {
        public:
            SdlGraphic(std::string &name, int size_x, int size_y);
            ~SdlGraphic();

            void init() override;
            void close() override;
            void render() override;

            bool pollEvent(Event &input) override;
            bool isOpen() override;

            float tick() override;

            void loadCanvas(std::shared_ptr<ICanvas> &canvas) override;
            void unloadCanvas(std::shared_ptr<ICanvas> &canvas) override;

            void destroy() override;
	        SDL_Window *_window;
        private:
            SDL_Renderer *_renderer;
            std::string _name;
            int _size_x;
            int _size_y;

    };
}
