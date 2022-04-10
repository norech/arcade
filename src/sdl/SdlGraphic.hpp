#pragma once

#include "../common/Graphic.hpp"
#include "spc/common/KeyCode.hpp"
#include "spc/graphic/IGraphic.hpp"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <unordered_map>

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

    void destroy() override;

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

 private:
    static std::unordered_map<int, KeyCode> _keyMap;
    std::string _name;
    bool _shouldClose;
    int _size_x;
    int _size_y;
};
}
