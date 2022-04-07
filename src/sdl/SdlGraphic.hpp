#pragma once

#include "../common/Graphic.hpp"
#include "spc/graphic/IGraphic.hpp"
#include "spc/common/KeyCode.hpp"
#include <iostream>
#include <SDL2/SDL_ttf.h>

namespace arc::grph {

class SdlGraphic : public AGraphic {
 public:
    SdlGraphic();
    ~SdlGraphic();

    void init() override;
    void close() override;
    void clear() override;
    void render() override;

    bool pollEvent(Event& input) override;
    bool isOpen() override;

    float tick() override;

    void loadCanvas(std::shared_ptr<ICanvas>& canvas) override;
    void unloadCanvas(std::shared_ptr<ICanvas>& canvas) override;

    void registerSprite(game::ISprite &sprite);

    void destroy() override;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    TTF_Font *_font;

 private:
    std::string _name;
    bool _shouldClose;
    int _size_x;
    int _size_y;
};
}
